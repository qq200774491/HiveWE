#define MI_MALLOC_OVERRIDE
#include <mimalloc.h>

#define QT_NO_OPENGL

#include <QApplication>
#include <QCoreApplication>
#include <QFile>
#include <QFont>
#include <QPalette>
#include <QSurfaceFormat>
#include <QSettings>
#include <QStyleFactory>
#include <QMessageBox>

#include "main_window/hivewe.h"
#include "DockManager.h"

#include <fstream>
#include <mutex>
#include <chrono>

#ifdef WIN32
// To force HiveWE to run on the discrete GPU if available
extern "C" {
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
}
#endif

int main(int argc, char* argv[]) {
	static std::mutex log_mutex;
	static std::ofstream log_file;
	auto log_line = [&](const QString& line) {
		std::lock_guard<std::mutex> lock(log_mutex);
		if (!log_file.is_open()) {
			log_file.open("startup.log", std::ios::app);
		}
		if (log_file.is_open()) {
			log_file << line.toStdString() << "\n";
			log_file.flush();
		}
	};

	qInstallMessageHandler(+[](QtMsgType type, const QMessageLogContext& ctx, const QString& msg) {
		static std::mutex handler_mutex;
		static std::ofstream handler_log;
		std::lock_guard<std::mutex> lock(handler_mutex);
		if (!handler_log.is_open()) {
			handler_log.open("startup.log", std::ios::app);
		}
		if (!handler_log.is_open()) {
			return;
		}
		QString prefix;
		switch (type) {
			case QtDebugMsg: prefix = "[debug] "; break;
			case QtInfoMsg: prefix = "[info] "; break;
			case QtWarningMsg: prefix = "[warn] "; break;
			case QtCriticalMsg: prefix = "[crit] "; break;
			case QtFatalMsg: prefix = "[fatal] "; break;
		}
		handler_log << (prefix + msg).toStdString() << "\n";
		handler_log.flush();
	});

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setStencilBufferSize(8);
	format.setVersion(4, 5);
	format.setProfile(QSurfaceFormat::CoreProfile);
	format.setOption(QSurfaceFormat::DebugContext);
	format.setSwapInterval(1);
	//format.setColorSpace(QSurfaceFormat::sRGBColorSpace);
	QSurfaceFormat::setDefaultFormat(format);

	QCoreApplication::setAttribute(Qt::AA_ShareOpenGLContexts);
	QCoreApplication::setOrganizationName("HiveWE");
	QCoreApplication::setApplicationName("HiveWE");

	QLocale::setDefault(QLocale("en_US"));

	// Create a dark palette
	// For some magically unknown reason Qt draws Qt::white text as black, so we use QColor(255, 254, 255) instead
	QPalette darkPalette;
	darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::WindowText, QColor(255, 254, 255));
	darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
	darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
	darkPalette.setColor(QPalette::ToolTipBase, QColor(66, 66, 66));
	darkPalette.setColor(QPalette::ToolTipText, QColor(255, 254, 255));
	darkPalette.setColor(QPalette::Text, QColor(255, 254, 255));
	darkPalette.setColor(QPalette::PlaceholderText, Qt::gray);
	darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::Dark, QColor(35, 35, 35));
	darkPalette.setColor(QPalette::Shadow, QColor(20, 20, 20));
	darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	darkPalette.setColor(QPalette::ButtonText, QColor(255, 254, 255));
	darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
	darkPalette.setColor(QPalette::BrightText, Qt::red);
	darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
	darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
	darkPalette.setColor(QPalette::HighlightedText, QColor(255, 254, 255));
	darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));

	QApplication::setPalette(darkPalette);
	QApplication::setStyle("Fusion");

	QApplication a(argc, argv);
	log_line("=== HiveWE startup ===");

	ads::CDockManager::setConfigFlag(ads::CDockManager::FocusHighlighting);
	ads::CDockManager::setConfigFlag(ads::CDockManager::AllTabsHaveCloseButton);
	ads::CDockManager::setConfigFlag(ads::CDockManager::DockAreaDynamicTabsMenuButtonVisibility);
	ads::CDockManager::setConfigFlag(ads::CDockManager::OpaqueSplitterResize);
	ads::CDockManager::setConfigFlag(ads::CDockManager::MiddleMouseButtonClosesTab);

	const QSettings settings;
	auto normalize_theme_name = [](QString theme) {
		theme = theme.trimmed();
		if (theme.compare("浅色", Qt::CaseInsensitive) == 0 || theme.compare("light", Qt::CaseInsensitive) == 0) {
			return QString("Light");
		}
		if (theme.compare("深色", Qt::CaseInsensitive) == 0 || theme.compare("dark", Qt::CaseInsensitive) == 0) {
			return QString("Dark");
		}
		return theme;
	};
	const QString theme = normalize_theme_name(settings.value("theme", "Dark").toString());
	QFile file("data/themes/" + theme + ".qss");
	if (!file.open(QIODevice::ReadOnly)) {
		qWarning() << "Error: Reading theme failed:" << file.error() << ": " << file.errorString();
		return -1;
	}

	a.setStyleSheet(QLatin1String(file.readAll()));

	try {
		HiveWE w;
		return QApplication::exec();
	} catch (const std::exception& e) {
		log_line(QString("[exception] ") + e.what());
		QMessageBox::critical(nullptr, "启动失败", QString("启动异常：\n%1").arg(e.what()));
		return -1;
	} catch (...) {
		log_line("[exception] unknown");
		QMessageBox::critical(nullptr, "启动失败", "启动异常：未知错误");
		return -1;
	}
}

#include "settings_editor.h"

#include <QSettings>
#include <QFile>

import std;

namespace {
	QString normalize_theme_name(QString theme) {
		theme = theme.trimmed();
		if (theme.compare("浅色", Qt::CaseInsensitive) == 0 || theme.compare("light", Qt::CaseInsensitive) == 0) {
			return "Light";
		}
		if (theme.compare("深色", Qt::CaseInsensitive) == 0 || theme.compare("dark", Qt::CaseInsensitive) == 0) {
			return "Dark";
		}
		return theme;
	}
}

void setTestArgs(Ui::SettingsEditor &ui) {
	ui.testArgs->setText(ui.userArgs->text() + " -mapdiff " + QString::fromStdString(std::string("") + char(ui.diff->currentIndex() + '0')) +
						(ui.windowmode->currentText() != "Default" ? " -windowmode " + QString([](int x) {
		switch (x) { case 1: return "windowed"; case 2: return "windowedfullscreen"; default: return "fullscreen";} }(ui.windowmode->currentIndex())) : "") +
						(ui.testhd->currentText() != "Default" ? " -hd " + QString([](int x) {
		switch (x) { case 1: return "1"; default: return "0";} }(ui.testhd->currentIndex())) : "") +
						(ui.testteen->currentText() != "Default" ? " -teen " + QString([](int x) {
		switch (x) { case 1: return "1"; default: return "0"; } }(ui.testteen->currentIndex())) : "") +
						" -testmapprofile " + ui.profile->text() + " -fixedseed " + (ui.fixedseed->isChecked() ? "1" : "0") + (ui.nowfpause->isChecked() ? " -nowfpause" : ""));
};

SettingsEditor::SettingsEditor(QWidget* parent)
	: QDialog(parent) {
	ui.setupUi(this);
	QSettings settings;
	ui.theme->setItemData(0, "Light");
	ui.theme->setItemData(1, "Dark");
	const QString theme = normalize_theme_name(settings.value("theme", "Dark").toString());
	int theme_index = ui.theme->findData(theme);
	if (theme_index < 0) {
		theme_index = ui.theme->findText(theme);
	}
	if (theme_index < 0) {
		theme_index = 1; // Dark default
	}
	ui.theme->setCurrentIndex(theme_index);
	ui.comments->setChecked(settings.value("comments", "True").toString() != "False");
	ui.flavour->setCurrentText(settings.value("flavour").toString());
	ui.hd->setChecked(settings.value("hd", "True").toString() != "False");
	ui.teen->setChecked(settings.value("teen", "False").toString() != "False");

	ui.userArgs->setText(settings.value("userArgs", "").toString());
	ui.diff->setCurrentText(settings.value("diff", "Normal").toString());
	ui.windowmode->setCurrentText(settings.value("windowmode", "Default").toString());
	ui.testhd->setCurrentText(settings.value("testhd", "Default").toString());
	ui.testteen->setCurrentText(settings.value("testteen", "Default").toString());
	ui.profile->setText(settings.value("profile", "HiveWE").toString());
	ui.fixedseed->setChecked(settings.value("fixedseed", "True").toString() != "False");
	ui.nowfpause->setChecked(settings.value("nowfpause", "True").toString() != "False");

	connect(ui.userArgs, &QLineEdit::textChanged, [&]() { setTestArgs(ui); });
	connect(ui.diff, &QComboBox::currentTextChanged, [&]() { setTestArgs(ui); });
	connect(ui.windowmode, &QComboBox::currentTextChanged, [&]() { setTestArgs(ui); });
	connect(ui.testhd, &QComboBox::currentTextChanged, [&]() { setTestArgs(ui); });
	connect(ui.testteen, &QComboBox::currentTextChanged, [&]() { setTestArgs(ui); });
	connect(ui.profile, &QLineEdit::textChanged, [&]() { setTestArgs(ui); });
	connect(ui.fixedseed, &QCheckBox::checkStateChanged, [&]() { setTestArgs(ui); });
	connect(ui.nowfpause, &QCheckBox::checkStateChanged, [&]() { setTestArgs(ui); });
	emit ui.nowfpause->checkStateChanged(Qt::CheckState::Unchecked);


	connect(ui.buttonBox, &QDialogButtonBox::accepted, [&]() {
		save();
		QSettings settings;
		const QString theme = normalize_theme_name(settings.value("theme").toString());
		QFile file("data/themes/" + theme + ".qss");
		file.open(QFile::ReadOnly);
		QString StyleSheet = QLatin1String(file.readAll());

		qApp->setStyleSheet(StyleSheet);
		emit accept();
		close();
	});

	connect(ui.buttonBox, &QDialogButtonBox::rejected, [&]() {
		emit reject();
		close();
	});
	show();
}

void SettingsEditor::save() const {
	QSettings settings;
	const QString theme = ui.theme->currentData().toString().isEmpty()
		? normalize_theme_name(ui.theme->currentText())
		: ui.theme->currentData().toString();
	settings.setValue("theme", theme);
	settings.setValue("flavour", ui.flavour->currentText());
	settings.setValue("comments", ui.comments->isChecked() ? "True" : "False");
	settings.setValue("hd", ui.hd->isChecked() ? "True" : "False");
	settings.setValue("teen", ui.teen->isChecked() ? "True" : "False");
	settings.setValue("userArgs", ui.userArgs->text());
	settings.setValue("diff", ui.diff->currentText());
	settings.setValue("windowmode", ui.windowmode->currentText());
	settings.setValue("testhd", ui.testhd->currentText());
	settings.setValue("testteen", ui.testteen->currentText());
	settings.setValue("profile", ui.profile->text());
	settings.setValue("fixedseed", ui.fixedseed->isChecked() ? "True" : "False");
	settings.setValue("nowfpause", ui.nowfpause->isChecked() ? "True" : "False");
	settings.setValue("testArgs", ui.testArgs->text());
}

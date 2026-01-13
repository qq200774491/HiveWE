module;

#include <QSettings>
#include <QPainter>
#include <QIcon>

export module OpenGLUtilities;

import std;
import ResourceManager;
import Texture;
import <glad/glad.h>;
import <glm/glm.hpp>;

namespace fs = std::filesystem;

export class Shapes {
  public:
	void init() {
		glCreateBuffers(1, &vertex_buffer);
		glNamedBufferData(vertex_buffer, quad_vertices.size() * sizeof(glm::vec2), quad_vertices.data(), GL_STATIC_DRAW);

		glCreateBuffers(1, &index_buffer);
		glNamedBufferData(index_buffer, quad_indices.size() * sizeof(unsigned int) * 3, quad_indices.data(), GL_STATIC_DRAW);
	}

	GLuint vertex_buffer;
	GLuint index_buffer;

	const std::vector<glm::vec2> quad_vertices = {
		{ 1, 1 },
		{ 0, 1 },
		{ 0, 0 },
		{ 1, 0 }
	};

	const std::vector<glm::uvec3> quad_indices = {
		{ 0, 1, 2 },
		{ 2, 3, 0 }
	};
};

export inline Shapes shapes;

/// Convert a Tground texture into an QIcon with two states
export QIcon ground_texture_to_icon(uint8_t* data, const int width, const int height) {
	QImage temp_image = QImage(data, width, height, QImage::Format::Format_RGBA8888);
	const int size = height / 4;

	auto pix = QPixmap::fromImage(temp_image.copy(0, 0, size, size));

	QIcon icon;
	icon.addPixmap(pix, QIcon::Normal, QIcon::Off);

	QPainter painter(&pix);
	painter.fillRect(0, 0, size, size, QColor(255, 255, 0, 64));
	painter.end();

	icon.addPixmap(pix, QIcon::Normal, QIcon::On);

	return icon;
}

/// Loads a texture from the hierarchy and returns an icon
export QIcon texture_to_icon(fs::path path) {
	auto tex = resource_manager.load<Texture>(path);
	QImage temp_image = QImage(tex->data.data(), tex->width, tex->height, tex->channels == 3 ? QImage::Format::Format_RGB888 : QImage::Format::Format_RGBA8888);
	auto pix = QPixmap::fromImage(temp_image);
	return QIcon(pix);
};

namespace {
	bool has_classic_mpq(const fs::path& directory) {
		return fs::exists(directory / "War3.mpq")
			|| fs::exists(directory / "war3.mpq")
			|| fs::exists(directory / "War3x.mpq")
			|| fs::exists(directory / "war3x.mpq")
			|| fs::exists(directory / "War3Patch.mpq")
			|| fs::exists(directory / "war3patch.mpq");
	}

	std::optional<fs::path> registry_war3_path() {
		const std::vector<QString> roots = {
			"HKEY_LOCAL_MACHINE",
			"HKEY_CURRENT_USER",
		};
		const std::vector<QString> subkeys = {
			"SOFTWARE\\Blizzard Entertainment\\Warcraft III",
			"SOFTWARE\\WOW6432Node\\Blizzard Entertainment\\Warcraft III",
		};
		const std::vector<QString> value_names = {
			"InstallPath",
			"Install Path",
			"GamePath",
		};

		for (const auto& root : roots) {
			for (const auto& subkey : subkeys) {
				QSettings reg(root + "\\" + subkey, QSettings::NativeFormat);
				for (const auto& name : value_names) {
					QString raw = reg.value(name).toString().trimmed();
					if (raw.isEmpty()) {
						continue;
					}
					if (raw.startsWith('\"') && raw.endsWith('\"') && raw.size() >= 2) {
						raw = raw.mid(1, raw.size() - 2);
					}
					const fs::path candidate = fs::path(raw.toStdWString());
					if (has_classic_mpq(candidate)) {
						return candidate;
					}
				}
			}
		}

		return std::nullopt;
	}
}

export fs::path find_warcraft_directory() {
	QSettings settings;
	if (settings.contains("warcraftDirectory")) {
		const fs::path saved = settings.value("warcraftDirectory").toString().toStdWString();
		if (has_classic_mpq(saved)) {
			return saved;
		}
	}

	if (const auto reg = registry_war3_path()) {
		return *reg;
	}

	const std::vector<fs::path> common_paths = {
		"C:/Program Files/Warcraft III",
		"C:/Program Files (x86)/Warcraft III",
		"D:/Warcraft III",
		"D:/Games/Warcraft III",
		"E:/Warcraft III",
		"E:/Games/Warcraft III",
	};

	for (const auto& path : common_paths) {
		if (has_classic_mpq(path)) {
			return path;
		}
	}

	return "";
}

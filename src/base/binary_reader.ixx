export module BinaryReader;

import std;
import types;
import no_init_allocator;

export class BinaryReader {
  public:
	std::vector<u8, default_init_allocator<u8>> buffer;
	unsigned long long int position = 0;
	std::string source;

	explicit BinaryReader(std::vector<u8, default_init_allocator<u8>> buffer, std::string source = {})
		: buffer(std::move(buffer)), source(std::move(source)) {
	}

	template <typename T>
	[[nodiscard]] T read() {
		static_assert(std::is_trivial_v<T>, "T must be of trivial type.");

		if (position + sizeof(T) > buffer.size()) {
			throw std::out_of_range(std::format(
				"Trying to read out of range of buffer (source={}, pos={}, size={}, need={})",
				source, position, buffer.size(), sizeof(T)
			));
		}

		T result;
		std::memcpy(&result, &buffer[position], sizeof(T));

		position += sizeof(T);
		return result;
	}

	[[nodiscard]] std::string read_string(const size_t size) {
		if (position + size > buffer.size()) {
			throw std::out_of_range(std::format(
				"Trying to read out of range of buffer (source={}, pos={}, size={}, need={})",
				source, position, buffer.size(), size
			));
		}

		std::string result;
		result.resize(size);
		std::memcpy(result.data(), &buffer[position], size);

		if (const size_t pos = result.find_first_of('\0', 0); pos != std::string::npos) {
			result.resize(pos);
		}

		position += size;
		return result;
	}

	[[nodiscard]] std::string read_c_string() {
		const std::string string(reinterpret_cast<char*>(buffer.data() + position));
		position += string.size() + 1;

		if (position > buffer.size()) {
			throw std::out_of_range(std::format(
				"Trying to read out of range of buffer (source={}, pos={}, size={})",
				source, position, buffer.size()
			));
		}

		return string;
	}

	template <typename T>
	[[nodiscard]] std::vector<T> read_vector(const size_t size) {
		static_assert(std::is_trivial_v<T>, "T must be of trivial type.");

		if (position + sizeof(T) * size > buffer.size()) {
			throw std::out_of_range(std::format(
				"Trying to read out of range of buffer (source={}, pos={}, size={}, need={})",
				source, position, buffer.size(), sizeof(T) * size
			));
		}
		std::vector<T> result(reinterpret_cast<T*>(&buffer[position]), reinterpret_cast<T*>(&buffer[position]) + size);
		position += sizeof(T) * size;
		return result;
	}

	[[nodiscard]] long long remaining() const {
		return buffer.size() - position;
	}

	void advance(const size_t amount) {
		if (position + amount > buffer.size()) {
			throw std::out_of_range(std::format(
				"Trying to advance past the end of the buffer (source={}, pos={}, size={}, need={})",
				source, position, buffer.size(), amount
			));
		}
		position += amount;
	}

	void advance_c_string() {
		position += std::string(reinterpret_cast<char*>(buffer.data() + position)).size() + 1;

		if (position > buffer.size()) {
			throw std::out_of_range("Trying to read out of range of buffer");
		}
	}
};

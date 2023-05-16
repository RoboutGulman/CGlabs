#pragma once
#include <vector>

class IndexBuffer
{
private:
	unsigned int m_rendererID;
	unsigned int m_count;

public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(const std::vector<GLuint>& vec);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return m_count; }
};

#pragma once

class VertexBuffer
{
protected:
	unsigned int m_id;
	VertexBuffer();
public:
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	inline unsigned int GetID() const { return m_id; };
};

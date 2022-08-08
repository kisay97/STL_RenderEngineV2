#pragma once

#include <Core/Core.h>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace STL
{
	// 서브 메시 - 스태틱 메시에서 배열로 저장할 하위 메시.
	class ENGINE_API SubMesh
	{
	public:

		void Create(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
			void* indices, uint32 indexCount, uint32 indexByteWidth = sizeof(uint32));
		void Bind(ID3D11DeviceContext* context);
		void Draw(ID3D11DeviceContext* context);

		uint32 index = 0;
		VertexBuffer vertexBuffer;
		IndexBuffer indexBuffer;
	};

	class ENGINE_API StaticMesh
	{
	public:
		StaticMesh();
		~StaticMesh();

		void AddSubMesh(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
			void* indices, uint32 indexCount, uint32 indexByteWidth = sizeof(uint32));

		void Create(ID3D11Device* device,
			void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
			void* indices, uint32 indexCount, uint32 indexByteWidth = sizeof(uint32));

		void Bind(ID3D11DeviceContext* context);
		void Draw(ID3D11DeviceContext* context);

	private:
		std::vector<SubMesh*> meshes;
	};
}
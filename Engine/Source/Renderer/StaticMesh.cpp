#include "Core.h"
#include "StaticMesh.h"

namespace STL
{
	//-- SubMesh
	void SubMesh::Create(ID3D11Device* device,
		void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
		void* indices, uint32 indexCount, uint32 indexByteWidth)
	{
		vertexBuffer = VertexBuffer(vertices, vertexCount, vertexByteWidth);
		vertexBuffer.Create(device);

		indexBuffer = IndexBuffer(indices, indexCount, indexByteWidth);
		indexBuffer.Create(device);
	}

	void SubMesh::Bind(ID3D11DeviceContext* context)
	{
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		vertexBuffer.Bind(context);
		indexBuffer.Bind(context);
	}

	void SubMesh::Draw(ID3D11DeviceContext* context)
	{
		//indexBuffer.Draw(context);
		context->DrawIndexed(indexBuffer.Count(), 0u, 0);
	}

	//-- StaticMesh

	StaticMesh::StaticMesh()
	{

	}

	StaticMesh::~StaticMesh()
	{
		for (auto mesh : meshes)
		{
			if (mesh != nullptr)
			{
				delete mesh;
				mesh = nullptr;
			}
		}
	}

	void StaticMesh::AddSubMesh(ID3D11Device* device,
		void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
		void* indices, uint32 indexCount, uint32 indexByteWidth)
	{
		SubMesh* mesh = new SubMesh();
		mesh->Create(device, vertices, vertexCount, vertexByteWidth, indices, indexCount, indexByteWidth);
		mesh->index = static_cast<uint32>(meshes.size());
		meshes.emplace_back(mesh);
	}

	void StaticMesh::Create(ID3D11Device* device,
		void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
		void* indices, uint32 indexCount, uint32 indexByteWidth)
	{
		SubMesh* mesh = new SubMesh();
		mesh->Create(device, vertices, vertexCount, vertexByteWidth, indices, indexCount, indexByteWidth);
		meshes.emplace_back(mesh);
	}

	void StaticMesh::Bind(ID3D11DeviceContext* context)
	{
		//for (auto mesh : meshes)
		//{
		//	mesh->Bind(context);
		//}
	}

	void StaticMesh::Draw(ID3D11DeviceContext* context)
	{
		for (auto mesh : meshes)
		{
			mesh->Bind(context);
			mesh->Draw(context);
		}
	}
}
#include "Core.h"
#include "StaticMesh.h"

namespace STL
{
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

	void StaticMesh::AddSubMesh(SubMesh* subMesh)
	{
		subMesh->index = static_cast<uint32>(meshes.size());
		meshes.emplace_back(subMesh);
	}

	void StaticMesh::Create(ID3D11Device* device,
		void* vertices, uint32 vertexCount, uint32 vertexByteWidth,
		void* indices, uint32 indexCount, uint32 indexByteWidth)
	{
		SubMesh* mesh = new SubMesh();
		mesh->Create(device, vertices, vertexCount, vertexByteWidth, indices, indexCount, indexByteWidth);
		meshes.emplace_back(mesh);
	}

	void StaticMesh::AddMaterial(Material* newMaterial)
	{
		materials.emplace_back(newMaterial);
	}

	void StaticMesh::SetMaterial(Material* newMaterial, uint32 index)
	{
		if (index < materials.size())
		{
			materials[index] = newMaterial;
		}
	}

	Material& StaticMesh::GetMaterial(uint32 index)
	{
		if (index >= materials.size())
		{
			throw std::exception("There's no materials with this index.");
		}

		return *materials[index];
	}

	void StaticMesh::Initialize(ID3D11Device* device)
	{
		for (auto material : materials)
		{
			material->Initialize(device);
		}
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
		//for (auto mesh : meshes)
		//{
		//	mesh->Bind(context);
		//	mesh->Draw(context);
		//}

		for (size_t ix = 0; ix < meshes.size(); ++ix)
		{
			auto mesh = meshes[ix];

			if (ix < materials.size())
			{
				materials[ix]->Bind(context);
			}

			mesh->Bind(context);
			mesh->Draw(context);
		}
	}
}
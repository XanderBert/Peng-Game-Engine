#pragma once
#include <memory>
#include "Transform.h"

namespace dae
{
	class Texture2D;

	// todo: this should become final.
	class GameObject
	{
	public:
		//Called each frame
		virtual void Update([[maybe_unused]] float deltaT);

		//Called at a fixed time step
		//Used for physics & networking
		virtual void FixedUpdate([[maybe_unused]] float fixedTimeStep);

		//Called after the Update()
		//Used for camera and deletion of objects -> Deletion could be handled by the double buffer pattern
		virtual void LateUpdate([[maybe_unused]] float deltaT);

		//Called each frame
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};
	};
}

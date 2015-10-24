//----STANDARD----
#include "stdio.h"

//----LIBRARY----
#include "libvolume/window/window.h"
#include "libvolume/engine/realm.h"
#include "libvolume/engine/voxelterrain.h"
#include "libvolume/generation/perlin.h"

//----LOCAL----
#include "settings.h"

void loadAt(glm::ivec3 pos, LibVolume::Engine::VoxelTerrain& terrain)
{
	if (terrain.existsAt(pos))
		return;

	LibVolume::Generation::PerlinNoise noise;

	terrain.loadAt(pos);
	auto region = terrain.getAt(pos);

	for (int x = 0; x < 32; x ++)
	{
		for (int y = 0; y < 32; y ++)
		{
			for (int z = 0; z < 32; z ++)
			{
				glm::vec3 loc = glm::vec3(region->location) + glm::vec3(x, y, z);
				loc += glm::vec3(0, 0, 60);
				float density = 0.0f;
				float scalar = 0.8;

				glm::vec3 offset = noise.getPerlinVec3(glm::vec4(loc.x * scalar, loc.y * scalar, scalar * loc.z * 1.0, 7.0) * 4.0f, -7.5, 1.0, 1.0);
				density = (-loc.z + 64.0f) / 20.0f + noise.getPerlin(glm::vec4(scalar * loc.x + offset.x * 20.0f, scalar * loc.y + offset.y * 20.0f, scalar * loc.z + offset.z * 20.0f, 2.0) * 3.0f, -7.5, 2.0, 1.0);

				density += 0.02f * noise.getPerlin(glm::vec4(50.0f * loc.x, 50.0f * loc.y, 50.0f * loc.z, 6.0) * 3.0f, -7.5, 1.0, 1.0);

				float variant = noise.getPerlin(glm::vec4(loc, 1.0) * 1.0f, -7.0, 3.0, 1.0);
				region->getAt(glm::ivec3(x, y, z))->density = 0.5 * (1.0 + variant);
				region->getAt(glm::ivec3(x, y, z))->density = (density + 1.0f) / 0.5f;
			}
		}
	}

	region->mesh->colour = glm::vec3(0.5, 2.0, 0.0);

	region->extract(LibVolume::Engine::MeshingAlgorithm::MarchingCubes);
}

int main(int argc, char* argv[])
{
	LibVolume::Window::Window window;
	window.setTitle("Nilts");

	LibVolume::Engine::Realm realm;
	realm.linkTo(window);

	realm.camera.state.position = glm::vec3(-20.0, 0.0, 0.0);

	LibVolume::Render::Structures::Light sun(LibVolume::Render::Structures::LightType::Directional, glm::vec3(0.25, 0.25, -1.0), glm::vec3(3.0, 3.0, 2.9), 0.05);
	realm.addLight(sun);

	LibVolume::Engine::VoxelTerrain terrain(glm::ivec3(32, 32, 32));

	for (int x = -1; x < 1; x ++)
	{
		for (int y = -1; y < 1; y ++)
		{
			for (int z = 0; z < 1; z ++)
			{
				loadAt(glm::ivec3(x, y, z), terrain);
				//terrain.getAt(glm::ivec3(x, y, z))->extract(LibVolume::Engine::MeshingAlgorithm::MarchingCubes);
			}
		}
	}

	for (int x = -1; x < 1; x ++)
	{
		for (int y = -1; y < 1; y ++)
		{
			for (int z = 0; z < 1; z ++)
			{
				terrain.getAt(glm::ivec3(x, y, z))->extract(LibVolume::Engine::MeshingAlgorithm::MarchingCubes);
			}
		}
	}

	realm.addObject(terrain);

	while (window.tick() == false)
	{
		if (window.event_manager.keyboard_state.key_down)
			realm.camera.state.position += (glm::f64vec3(0.0, 0.0, 3.0) * 0.05) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_right)
			realm.camera.state.position += (glm::f64vec3(3.0, 0.0, 0.0) * 0.05) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_left)
			realm.camera.state.position += (glm::f64vec3(-3.0, 0.0, 0.0) * 0.05) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_up)
			realm.camera.state.position += (glm::f64vec3(0.0, 0.0, -3.0) * 0.05) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_space)
			realm.camera.state.position += (glm::f64vec3(0.0, 3.0, 0.0) * 0.05) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_shift)
			realm.camera.state.position += (glm::f64vec3(0.0, -3.0, 0.0) * 0.05) * realm.camera.state.orientation;

		if (window.event_manager.keyboard_state.key_a)
			realm.camera.state.orientation = glm::f64quat(glm::vec3(0.0, -0.03, 0.0)) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_d)
			realm.camera.state.orientation = glm::f64quat(glm::vec3(0.0, 0.03, 0.0)) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_w)
			realm.camera.state.orientation = glm::f64quat(glm::vec3(0.03, 0.0, 0.0)) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_s)
			realm.camera.state.orientation = glm::f64quat(glm::vec3(-0.03, 0.0, 0.0)) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_q)
			realm.camera.state.orientation = glm::f64quat(glm::vec3(0.0, 0.0, -0.03)) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_e)
			realm.camera.state.orientation = glm::f64quat(glm::vec3(0.0, 0.0, 0.03)) * realm.camera.state.orientation;

		for (int x = -1; x < 1; x ++)
		{
			for (int y = -1; y < 1; y ++)
			{
				for (int z = -1; z < 1; z ++)
				{
					loadAt(glm::ivec3(x, y, z) + glm::ivec3(realm.camera.state.position) / 32, terrain);
					//terrain.getAt(glm::ivec3(x, y, z))->extract(LibVolume::Engine::MeshingAlgorithm::MarchingCubes);
				}
			}
		}

		realm.tick();
		realm.render();
	}

	return 0;
}

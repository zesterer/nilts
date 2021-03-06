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
	std::vector<glm::vec3> colours = {glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.4f, 0.9f, 0.4f), glm::vec3(1.3f, 1.3f, 4.0f), glm::vec3(4.5f, 3.7f, 3.0f), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(4.6f, 4.6f, 4.6f)};

	if (terrain.existsAt(pos))
		return;

	LibVolume::Generation::PerlinNoise noise;

	terrain.loadAt(pos);
	LibVolume::Engine::VoxelTerrainChild* region = terrain.getAt(pos);

	for (int x = 0; x < 32; x ++)
	{
		for (int y = 0; y < 32; y ++)
		{
			for (int z = 0; z < 32; z ++)
			{
				LibVolume::Data::Voxel* voxel = region->getAt(glm::ivec3(x, y, z));

				glm::vec3 loc = (glm::vec3(region->location) + glm::vec3(x, y, z)) * 0.8f;
				float density = 0.0f;

				float var = (noise.getPerlin(glm::vec4(loc, 7.0), -6, 3.0, 2.6) + 1.0f) * 0.5f;
				density = glm::max(0.0f, glm::min(1.0f, 16.0f * var / (loc.z - 16.0f)));

				glm::vec2 caves;
				caves.x = glm::abs(noise.getPerlin(glm::vec4(loc, 14.0f), -6, 1.0, 1.0));
				caves.y = glm::abs(noise.getPerlin(glm::vec4(loc + glm::vec3(33.0f, 57.0f, 60.0f), 8.0f), -6, 1.0, 1.0));
				if (caves.x < 0.12f && caves.y < 0.12f)
					density *= glm::min(400.0f * caves.x * caves.y, 1.0f);

				voxel->density = density;

				if (loc.z + caves.x * 4.0f < 28.0f)
					voxel->type = 2;
				else if (loc.z + caves.y * 4.0f < 30.0f)
					voxel->type = 3;
				else if (loc.z < 37.0f)
					voxel->type = 1;
				else if (loc.z < 39.0f)
					voxel->type = 4;
				else
					voxel->type = 5;
			}
		}
	}

	region->colour_table = colours;

	terrain.reMesh(pos);
}

int main(int argc, char* argv[])
{
	LibVolume::Window::Window window;
	window.setTitle("Nilts");

	LibVolume::Engine::Realm realm;
	realm.linkTo(window);

	realm.background_colour = glm::vec3(4.0, 3.0, 8.0) * 0.2f;

	//Move a kilometre out
	realm.camera.state.position = glm::vec3(1000.0, 1000.0, 64.0);

	LibVolume::Render::Structures::Light sun(LibVolume::Render::Structures::LightType::Directional, glm::vec3(0.8, 0.25, -1.0), glm::vec3(3.0, 3.0, 3.9) * 0.4f, 0.2);
	realm.addLight(sun);

	LibVolume::Engine::VoxelTerrain terrain(glm::ivec3(32, 32, 32), LibVolume::Engine::MeshingAlgorithm::MarchingCubes, false, true);

	realm.addObject(terrain);

	while (window.tick() == false)
	{
		glm::f64vec3 new_camera_position = realm.camera.state.position;

		if (window.event_manager.keyboard_state.key_down)
			new_camera_position += (glm::f64vec3(0.0, 0.0, 3.0) * 0.02) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_right)
			new_camera_position += (glm::f64vec3(3.0, 0.0, 0.0) * 0.02) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_left)
			new_camera_position += (glm::f64vec3(-3.0, 0.0, 0.0) * 0.02) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_up)
			new_camera_position += (glm::f64vec3(0.0, 0.0, -3.0) * 0.02) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_space)
			new_camera_position += (glm::f64vec3(0.0, 3.0, 0.0) * 0.02) * realm.camera.state.orientation;
		if (window.event_manager.keyboard_state.key_shift)
			new_camera_position += (glm::f64vec3(0.0, -3.0, 0.0) * 0.02) * realm.camera.state.orientation;

		//Stop the camera moving if it's going to go inside the terrain
		/*if (terrain.existsAt((glm::vec3)(new_camera_position / 32.0)))
		{
			if (terrain.getAt((glm::vec3)new_camera_position / 32.0f)->getDensityAt(glm::mod((glm::vec3)new_camera_position, 32.0f)) < 0.5)
				realm.camera.state.position = new_camera_position;
		}
		else*/
			realm.camera.state.position = new_camera_position;

		if (terrain.existsAt((glm::vec3)(realm.camera.state.position / 32.0)))
		{
			while (terrain.getAt((glm::vec3)realm.camera.state.position / 32.0f)->getDensityAt(glm::mod((glm::vec3)realm.camera.state.position, 32.0f)) > 0.5)
			{
				realm.camera.state.position += terrain.getAt((glm::vec3)new_camera_position / 32.0f)->getNormalAt(glm::mod((glm::vec3)new_camera_position, 32.0f)) * 0.01f;
			}
		}

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

		for (int x = -2; x < 3; x ++)
		{
			for (int y = -2; y < 3; y ++)
			{
				for (int z = 0; z < 2; z ++)
				{
					loadAt(glm::ivec3(x, y, z) + glm::ivec3(realm.camera.state.position.x, realm.camera.state.position.y, 0) / 32, terrain);
					//terrain.getAt(glm::ivec3(x, y, z))->extract(LibVolume::Engine::MeshingAlgorithm::MarchingCubes);
				}
			}
		}

		realm.tick();
		realm.render();
	}

	return 0;
}

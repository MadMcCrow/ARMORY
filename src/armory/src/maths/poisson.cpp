/// Copyright (c) 2023 Noé Perard-Gayot (MadMcCrow)
/// This work is licensed under the terms of the MIT license. For a copy see <https://opensource.org/licenses/MIT>

// armory
#include "maths/poisson.hpp"
#include "maths/random.hpp"

using namespace ARMORY;

// TODO : read these from a settings resource
// TODO : allow for non-rectangular regions
// basically a 1,1 rectangle
// sample_region_shape - takes any of the following a Rect2 for rectangular region (see https://github.com/udit/poisson-disc-sampling for more variants)
//Rect2 _sample_region_rect;
static const float region_x = 1.f;
static const float region_y = 1.f;
// retries - maximum number of attempts to look around a sample point, reduce this value to speed up generation
static const int retries = 10;

void Poisson::generate()
{
	// spawn our random number generator
	Random rand;
	rand.init(_seed);

	// where to start : ie, the first sample
	Vector2 start_pos(
		(region_x) * rand.randf(),
		(region_y) * rand.randf()
	);

	const float cell_size = _radius / fsqrt(2);
	int cols = std::max(std::floor(region_x / cell_size), 1.f);
	int rows = std::max(std::floor(region_y / cell_size), 1.f);

	// scale the cell size in each axis 
	Vector2 cell_size_scaled(region_x / cols, region_y / rows);

	Array2D<int> grid;
	grid.resize(cols, rows, -1);
	
	std::vector<Vector2> spawn_points;

	spawn_points.push_back(start_pos);
	
	const auto is_valid_sample = [&](Vector2 sample) -> bool {
		if ( sample.x < region_x && sample.y < region_y)
		{
		Vector2 cell(int((sample.x) / cell_size_scaled.x), int(( sample.y) / cell_size_scaled.y));
		Vector2 cell_start(std::max(0.f, cell.x - 2.f), std::max(0.f, cell.y - 2.f));
		Vector2 cell_end(std::min(cell.x + 2.f, cols - 1.f), std::min(cell.y + 2.f, rows - 1.f));
	
		for (auto i = cell_start.x; i <= cell_end.x; i++)
		{
			for (auto j = cell_start.y; j <= cell_end.y; i++)
			{
				int search_index = grid.at(i,j);
				if (search_index != -1)
				{
					float dist = _points[search_index].distance_to(sample);
					if (dist < _radius)
					{
						return false;
					}
				}
			}
		}
		return true;
	}
	return false;
	};


	while (spawn_points.size() > 0 && _points.size() < _number )
	{
		int spawn_index = rand.randi() % spawn_points.size();
		Vector2 spawn_centre = spawn_points[spawn_index];
		bool sample_accepted = false;

		for (int i = retries; i -->0;)
		{
			float angle = 2 * F_PI * rand.randf();
			Vector2 sample = spawn_centre +
			 Vector2(cos(angle), sin(angle)) *
			 (_radius + _radius * rand.randf());
			 
			if (is_valid_sample(sample))
			{
				grid.at(
					int((0 + sample.x) / cell_size_scaled.x),
					int((0 + sample.y) / cell_size_scaled.y))
					= _points.size();
				_points.push_back(sample);
				spawn_points.push_back(sample);
				sample_accepted = true;
				break;
			}
		}
		if (!sample_accepted)
		{
			spawn_points.erase(spawn_points.begin() + spawn_index);
		}		
	}
	//return points;
}

void Poisson::_bind_methods()
{
	BIND_STATIC_METHOD_PARAMS(Poisson, generate_vectors, "number", "seed", "radius");
	BIND_STATIC_METHOD_PARAMS(Poisson, generate_points,  "number", "seed", "radius", "size");
}

TypedArray<Vector2> Poisson::generate_vectors(int number, int seed, float radius )
{
	Poisson poisson;
	poisson._seed = seed;
	poisson._number = number;
	poisson._radius = radius;
	poisson.generate();
	TypedArray<Vector2> vectors;
	for (const auto& p : poisson._points)
	{
		vectors.append(p);
	}
	return vectors;
}

TypedArray<Vector2i> Poisson::generate_points(int number, int seed , int radius, Vector2i size)
{
	Poisson poisson;
	poisson._seed = seed;
	poisson._number = number;
	poisson._radius = static_cast<float>(radius) / std::min(size.x, size.y);
	poisson.generate();
	TypedArray<Vector2i> points;
	for(const auto& vector: poisson._points)
	{
		const auto p = Vector2i(
			static_cast<int>(round(vector.x * size.x)),
			static_cast<int>(round(vector.y * size.y))
		);
		if (!points.has(p))
		{
			points.append(p);
		}
	}
	return points;
}
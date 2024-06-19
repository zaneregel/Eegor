#include "Transform.h"
#include "Entity.h"

namespace eegor::transform
{
	namespace {

		utl::vector<math::v3> positions;
		utl::vector<math::v4> rotations;
		utl::vector<math::v3> scales;

	} // anonymous namespace

	component 
	create_transform(const init_info& info, game_entity::entity entity)
	{
		assert(entity.is_valid());
		const id::id_type entity_index{ id::index(entity.get_id()) };

		if (positions.size() > entity_index) //if positions is u32 and entity is u16 then this will fill holes in the entity array
		{
			rotations[entity_index] = math::v4(info.rotation);
			positions[entity_index] = math::v3(info.position);
			scales[entity_index] = math::v3(info.scale);
		}
		else
		{
			assert(positions.size() == entity_index);
			rotations.emplace_back(info.rotation);
			positions.emplace_back(info.position);
			scales.emplace_back(info.scale);
		}

		return component{ transform_id{ entity.get_id() } };
	}
	void 
	remove_transform(component c) 
	{
		assert(c.is_valid());
	}

	math::v4 
	component::rotation() const
	{
		assert(is_valid());
		return rotations[id::index(_id)];
	}
	math::v3 
	component::position() const
	{
		assert(is_valid());
		return positions[id::index(_id)];
	}
	math::v3 
	component::scale() const
	{
		assert(is_valid());
		return scales[id::index(_id)];
	}
}
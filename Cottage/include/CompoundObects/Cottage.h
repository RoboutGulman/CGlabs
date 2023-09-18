#pragma once
#include "CompoundObject.h"
#include "Fence.h"
#include "Garage.h"
#include "Grass.h"
#include "LivingRoom.h"
#include "Bedroom.h"
#include "DiningRoom.h"

class Cottage : public CompoundObject
{
public:
	Cottage()
	{
		std::unique_ptr<IDrawable> livingRoom = std::make_unique<LivingRoom>();
		std::unique_ptr<IDrawable> grass = std::make_unique<Grass>();
		std::unique_ptr<IDrawable> garage = std::make_unique<Garage>();
		std::unique_ptr<IDrawable> fence = std::make_unique<Fence>();
		std::unique_ptr<IDrawable> bedroom = std::make_unique<Bedroom>();
		std::unique_ptr<IDrawable> diningRoom = std::make_unique<DiningRoom>();
		

		m_parts.push_back(std::move(livingRoom));
		m_parts.push_back(std::move(grass));
		m_parts.push_back(std::move(garage));
		m_parts.push_back(std::move(fence));
		m_parts.push_back(std::move(bedroom));
		m_parts.push_back(std::move(diningRoom));
	}
};

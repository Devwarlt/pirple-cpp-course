#include "BreedingConstraints.hpp"

using namespace breeding;

dog::dog(
	const char * & name, int & age, float & weight,
	breed_entry entry)
{
	this->name = name;
	this->age = age;
	this->weight = weight;
	this->entry = entry;
}

dog::~dog()
{
	delete &this->entry;
}

auto dog::get_premium(void) -> float
{
	auto base = this->get_base_premium();
	if (this->entry.subject_to_senior_discount && this->age > constants::SENIOR_AGE)
		base -= base * constants::ADDITIONAL_SENIOR_DISCOUNT;
	if (this->weight > constants::WEIGHT_CHARGE)
		base += base * constants::ADDITIONAL_WEIGHT_CHARGE;
	return base;
}

auto dog::get_base_premium(void) -> float
{
	return this->weight < entry.risk_weight
		? entry.below_risk_weight
		: entry.high_risk_weight;
}

other_breed::other_breed(
	const char * & name, int & age, float & weight,
	breed_entry entry)
	: dog(name, age, weight, entry) { }

other_breed::~other_breed()
{ }

auto other_breed::get_base_premium(void) -> float
{
	return entry.below_risk_weight;
}

auto breeding::factory::get_dog(
	const char *& name, int & age, float & weight,
	breed_entry entry) -> dog *
{
	auto instance = new dog(name, age, weight, entry);
	return instance;
}

auto breeding::factory::get_other_dog(
	const char *& name, int & age, float & weight,
	breed_entry entry) -> other_breed *
{
	auto instance = new other_breed(name, age, weight, entry);
	return instance;
}

#include "BreedingConstraints.hpp"

breeding::constraints::dog::dog(
	const char * & name, int & age, float & weight,
	breeding::constraints::breed_entry entry)
{
	this->name = name;
	this->age = age;
	this->weight = weight;
	this->entry = entry;
}

breeding::constraints::dog::~dog()
{
	delete &this->name;
	delete &this->age;
	delete &this->weight;
	delete &this->entry;
}

inline auto breeding::constraints::dog::get_premium(void) -> float
{
	auto base = this->get_base_premium();
	if (this->entry.subject_to_senior_discount && this->age > breeding::SENIOR_AGE)
		base -= base * breeding::ADDITIONAL_SENIOR_DISCOUNT;
	if (this->weight > breeding::WEIGHT_CHARGE)
		base += base * breeding::ADDITIONAL_WEIGHT_CHARGE;
	return base;
}

inline auto breeding::constraints::dog::get_base_premium(void) -> float
{
	return this->weight < entry.risk_weight
		? entry.below_risk_weight
		: entry.high_risk_weight;
}

breeding::constraints::other_breed::other_breed(
	const char * & name, int & age, float & weight,
	breeding::constraints::breed_entry entry)
	: dog(name, age, weight, entry) { }

breeding::constraints::other_breed::~other_breed()
{
	delete &this->name;
	delete &this->age;
	delete &this->weight;
	delete &this->entry;
}

inline auto breeding::constraints::other_breed::get_base_premium(void) -> float
{
	return entry.below_risk_weight;
}

inline auto breeding::dog_factory::get_dog(
	const char * & name, int & age, float & weight,
	breeding::constraints::breed_entry entry) -> breeding::constraints::dog *
{
	auto dog = new breeding::constraints::dog(name, age, weight, entry);
	return dog;
}

inline auto breeding::dog_factory::get_other_dog(
	const char * & name, int & age, float & weight,
	breeding::constraints::breed_entry entry) -> breeding::constraints::other_breed *
{
	auto dog = new breeding::constraints::other_breed(name, age, weight, entry);
	return dog;
}

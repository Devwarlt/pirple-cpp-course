#ifndef BREEDING_CONSTRAINTS_HPP_
#define BREEDING_CONSTRAINTS_HPP_
namespace breeding {
	namespace constants {
		const int SENIOR_AGE = 13;
		const float ADDITIONAL_SENIOR_DISCOUNT = 0.20F;

		const float WEIGHT_CHARGE = 50.00F;
		const float ADDITIONAL_WEIGHT_CHARGE = 0.25F;
	}

	typedef struct {
		const char * breed;
		int risk_weight;
		bool subject_to_senior_discount;
		float below_risk_weight;
		float high_risk_weight;
	} breed_entry;

	class dog
	{
	public:
		dog(const char * & name, int & age, float & weight, breed_entry entry);
		virtual ~dog();
		auto get_premium(void) -> float;
	protected:
		const char * name;
		int age;
		float weight;
		breed_entry entry;
		virtual float get_base_premium(void);
	};

	class other_breed : public dog {
	public:
		other_breed(const char * & name, int & age, float & weight, breed_entry entry);
		~other_breed();
	private: auto get_base_premium(void) ->float override;
	};

	namespace factory {
		auto get_dog(const char * & name, int & age, float & weight, breed_entry entry)->dog *;
		auto get_other_dog(const char * & name, int & age, float & weight, breed_entry entry)->other_breed *;
	}
}
#endif // !BREEDING_CONSTRAINTS_HPP_

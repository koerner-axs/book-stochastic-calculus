#include <iostream>
#include <vector>


double price_european_call() {
	const double strike = 5.0;
	const double initial_stock_price = 4.0;
	const double up = 1.05;
	const double down = 1 / up;
	uint16_t num_iterations = 356;
	const double interest_rate = std::pow(1.05, 1.0 / num_iterations) - 1.0;

	const double p_tilde = (1 + interest_rate - down) / (up - down);
	const double q_tilde = (up - 1 - interest_rate) / (up - down);

	std::vector<double> mem(num_iterations + 1);
	// Compute prices at expiry
	for (uint32_t index = 0; index <= num_iterations; index++) {
		mem[index] = std::max(0.0, (initial_stock_price * std::pow(up, num_iterations - 2 * (int64_t)index)) - strike);
	}
	double p_bar = 1 / (1 + interest_rate) * p_tilde;
	double q_bar = 1 / (1 + interest_rate) * q_tilde;
	while (num_iterations >= 1) {
		// Use recursive valuation formula to work back in time
		for (uint32_t index = 0; index < num_iterations; index++) {
			mem[index] = p_bar * mem[index] + q_bar * mem[index + 1];
		}
		num_iterations--;
	}

	return mem[0];
}


double price_european_put() {
	const double strike = 5.0;
	const double initial_stock_price = 4.0;
	const double up = 1.05;
	const double down = 1 / up;
	uint16_t num_iterations = 356;
	const double interest_rate = std::pow(1.05, 1.0 / num_iterations) - 1.0;

	const double p_tilde = (1 + interest_rate - down) / (up - down);
	const double q_tilde = (up - 1 - interest_rate) / (up - down);

	std::vector<double> mem(num_iterations + 1);
	// Compute prices at expiry
	for (uint32_t index = 0; index <= num_iterations; index++) {
		mem[index] = std::max(0.0, strike - (initial_stock_price * std::pow(up, num_iterations - 2 * (int64_t)index)));
	}
	double p_bar = 1 / (1 + interest_rate) * p_tilde;
	double q_bar = 1 / (1 + interest_rate) * q_tilde;
	while (num_iterations >= 1) {
		// Use recursive valuation formula to work back in time
		for (uint32_t index = 0; index < num_iterations; index++) {
			mem[index] = p_bar * mem[index] + q_bar * mem[index + 1];
		}
		num_iterations--;
	}

	return mem[0];
}


int main() {
	std::cout << "Value of call " << price_european_call() << std::endl;
	std::cout << "Value of put " << price_european_put() << std::endl;
}

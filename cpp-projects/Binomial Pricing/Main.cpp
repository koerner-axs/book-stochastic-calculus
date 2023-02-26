#include <iostream>
#include <vector>


double price_on_expiry(double stock_price) {
	return std::max(0.0, 5.0 - stock_price);
}


int main() {
	const double initial_stock_price = 4.0;
	const double up = 1.05;
	const double down = 1 / up;
	uint16_t num_iterations = 356;
	const double interest_rate = std::pow(1.05, 1.0 / num_iterations) - 1.0;

	const double p_tilde = (1 + interest_rate - down) / (up - down);
	const double q_tilde = (up - 1 - interest_rate) / (up - down);

	std::vector<double> mem(num_iterations + 1);
	for (uint32_t index = 0; index <= num_iterations; index++) {
		mem[index] = price_on_expiry(initial_stock_price * std::pow(up, num_iterations - 2 * (int64_t)index));
	}
	double p_bar = 1 / (1 + interest_rate) * p_tilde;
	double q_bar = 1 / (1 + interest_rate) * q_tilde;
	while (num_iterations >= 1) {
		for (uint32_t index = 0; index < num_iterations; index++) {
			mem[index] = p_bar * mem[index] + q_bar * mem[index + 1];
		}
		num_iterations--;
	}

	std::cout << "Value " << mem[0] << std::endl;
}

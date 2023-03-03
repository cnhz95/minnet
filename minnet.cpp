#include <iostream>
#include <limits>
#include <new>

int main() {
	constexpr int64_t KIB = 1024;
	constexpr int64_t GIB = 1073741824;

	auto allocate = [&](int64_t size) -> void {
		constexpr int64_t MIB = 1048576;
		int64_t total_allocated = 0;
		while (true) {
			try {
				new int64_t[size / 8];
				total_allocated += size / 8 * sizeof(int64_t);
				if (size == KIB && total_allocated % MIB == 0) {
					std::cout << "Hittills har " << total_allocated << " byte allokerats\n";
				}
				else if (size == GIB) {
					std::cout << "Hittills har " << total_allocated << " byte allokerats\n";
				}
			}
			catch (const std::bad_alloc& error) {
				std::cerr << "Allokeringen misslyckades: " << error.what() << '\n';
				break;
			}
		}
	};
	
	while (true) {
		std::cout << "\n\tVälkommen till startmenyn\n";
		std::cout << "--------------------------------------\n";
		std::cout << "Följande chunkstorlekar kan allokeras:\n";
		std::cout << "1) 1 GiB\n";
		std::cout << "2) 1 KiB\n";
		std::cout << "--------------------------------------\n";
		std::cout << "Vänligen välj alternativ: ";
		int64_t size;
		std::cin >> size;
		if (size == 1 || size == 2) {
			switch (size) {
			case 1:
				allocate(GIB);
				break;
			case 2:
				allocate(KIB);
				break;
			default:
				std::cerr << "Felaktigt alternativ. Vänligen försök igen.\n";
			}
		}
		else {
			std::cin.clear(); // Ta bort felflaggan som sattes vid felaktig inmattning
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cerr << "\nFelaktigt alternativ. Tryck enter för att försöka igen.";
			std::cin.ignore();
		}
	}

	return 0;
}
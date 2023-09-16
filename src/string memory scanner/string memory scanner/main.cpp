#include "..\string memory scanner\scanner\scanner.h"

int main()
{
	
	std::string stringtofind = "cat"; // the string that need to be founded
	scanner scanscan(6372); // procress id
	scanscan.scanstring(stringtofind); 

	// loop all addreses that the scanner found
	int count = 0;
	for (auto& addressaddress : scanscan.returnaddreses())
	{
		count++;
		std::cout << "string " << stringtofind << " found at address " << std::hex << addressaddress << std::dec << " count [" << count << "] \n";
	}
	std::cout << count << " strings found";
	std::cin.get();
	
}

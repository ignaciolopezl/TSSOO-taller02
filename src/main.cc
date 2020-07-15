#include <global.h>
#include <checkArgs.hpp>

uint64_t* Arreglo = nullptr;
uint64_t* sumaT = nullptr;
uint64_t* ArregloSerial = nullptr;
uint64_t sumaSerial = 0;


void rellenado( size_t inicio , size_t fin, size_t tipo ,uint64_t limSupRand , uint64_t limInfRand){
	
		std::random_device device;
		std::mt19937 rng(device());
		std::uniform_int_distribution<uint32_t> nRandom(limInfRand, limSupRand);
		uint32_t number = nRandom(rng);
		for(size_t i = inicio; i < fin; ++i){		
			switch(tipo){
				case 0: 
					ArregloSerial[i] = number;
					
					break;
				case 1:
					Arreglo[i] = number;
					
					break;
			}
		}
}

void suma( size_t inicio , size_t fin, size_t tipo, size_t hilo){
	

		for(size_t i = inicio; i < fin; ++i){		
			switch(tipo){
				case 0: 
					sumaSerial += Arreglo[i];
					
					break;
				case 1:
					sumaT[hilo] += Arreglo[i];
					
					
					break;
			}
		}
	
}


	



int main(int argc, char** argv){
	
	uint64_t tamanoArreglo;
	uint64_t numThreads;
	uint64_t limiteSuperior;
	uint64_t limiteInferior;
	uint64_t sumaTotal = 0;
	
	std::vector<std::thread*> threads;
	std::vector<std::thread*> threadsSuma;
	
	auto argumentos = (std::shared_ptr<checkArgs>) new checkArgs(argc, argv);
	
	tamanoArreglo = argumentos->getArgs().tamArreglo;
	numThreads     = argumentos->getArgs().numThreads;
	limiteSuperior = argumentos->getArgs().limSuperior;
	limiteInferior = argumentos->getArgs().limInferior;
	Arreglo = new uint64_t[tamanoArreglo];

	sumaT = new uint64_t[numThreads];

//-----------llenado paralelo----------------------//	
	auto start = std::chrono::high_resolution_clock::now();

	for(size_t i = 0; i < numThreads; ++i){
		threads.push_back( new std::thread(rellenado,
								i*(tamanoArreglo)/numThreads,
								(i+1)*(tamanoArreglo)/numThreads,1,limiteSuperior,limiteInferior));
	}

	for(auto& th : threads){
		th->join();
	}
	auto end     = std::chrono::high_resolution_clock::now(); 
	auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTime01 = elapsed.count();
//---------------llenado serial---------------------//
	
	

	ArregloSerial = new uint64_t[tamanoArreglo];
	start = std::chrono::high_resolution_clock::now();

	
	rellenado (0, tamanoArreglo, 0,limiteInferior,limiteSuperior );

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeFill_threads = elapsed.count();
//---------------suma paralela--------------------//
	start = std::chrono::high_resolution_clock::now();
	for(size_t i = 0; i < numThreads; ++i){
		threadsSuma.push_back( new std::thread(suma,
								i*(tamanoArreglo)/numThreads,
								(i+1)*(tamanoArreglo)/numThreads,1,i));
	}
	 
	for(auto& th : threadsSuma){
		th->join();
	}

	for (size_t i = 0; i < numThreads; i++)
	{

		sumaTotal = sumaT[i] + sumaTotal;
	}
	
	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeFill_threads2 = elapsed.count();
//--------------suma serial----------------------//
	start = std::chrono::high_resolution_clock::now();

	suma (0, tamanoArreglo, 0 ,0);
	

	end     = std::chrono::high_resolution_clock::now(); 
	elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	auto totalTimeFill_threads3 = elapsed.count();
	
	std::cout << "tamaño arreglo: " << tamanoArreglo << std::endl;
	std::cout << "Threads  : " << numThreads     << std::endl;
	std::cout << "limite inferior: " << limiteInferior << std::endl;
	std::cout << "limte superior  : " << limiteSuperior << std::endl;

	printf("suma total serial: %ld \n",sumaSerial);
	printf("suma total paralelo: %ld \n",sumaTotal);
	std::cout << "Tiempo llenado paralelo :"  << totalTime01 << "[ms]" << std::endl;
	std::cout << "Tiempo llenado serial :"  << totalTimeFill_threads << "[ms]" << std::endl;
	std::cout << "Tiempo suma paralela :"  << totalTimeFill_threads2 << "[ms]" << std::endl;
	std::cout << "Tiempo suma serial :"  << totalTimeFill_threads3 << "[ms]" << std::endl;

	
	
	return(EXIT_SUCCESS);
}


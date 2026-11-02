A organização final dos arquivos no  projeto:
* sync_car-runner.c: Contém a função main() que roda os testes da simulação.
//
* sync_car.c: Contém a lógica da estação (station_init, station_load_car, station_wait_for_car, station_on_board), sem conter a função main.
//
* sync_car.h: Declara a struct station e os protótipos das funções, servindo de ponte para que o sync_car-runner.c consiga chamar o seu código.
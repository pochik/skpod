#### Разработка параллельной версии программы для вычисления определителя матрицы приведением к верхнетреугольному виду.

### Compile
`cd build`   
`make`

### Запуск заданий
#### Polus
##### MPI 
`python job_loader_pl.py -mpi`

##### OMP
`python job_loader_pl.py -omp` 

#### Сбор результатов
`python results_collector.py` 

#### Построение графиков
`python analyzer.py`

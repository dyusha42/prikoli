#!/bin/bash

echo "Информация о процессоре:"
sysctl -n machdep.cpu.brand_string

echo "Запуск программы сортировки..."
./prikoluha

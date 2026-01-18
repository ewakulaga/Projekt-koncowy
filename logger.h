#ifndef LOGGER_H
#define LOGGER_H

#include "pso.h"

int open_logger(const char *plik);

void logger_log(int iter, const Swarm *swarm);

void close_logger(void);




#endif
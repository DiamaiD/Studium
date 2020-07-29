// Copyright 2020, Viktor Gange,
// Author: Viktor Gange <viktor.gange@gmail.com>

#include "./Trader.h"

Trader::Trader() {
  _verbose = false;
  _money = 0.0;
  _seedMoney = 0.0;
  _numBitcoins = 0;
  _lastPrices = new double[4];
  _lastPrices[0] = 0.0;
  _lastPrices[1] = 0.0;
  _lastPrices[2] = 0.0;
  _lastPrices[3] = 0.0;
}

Trader::~Trader() {
  delete[] _lastPrices;
}

void Trader::trade(double exchange) {
  _lastPrices[0] = _lastPrices[1];
  _lastPrices[1] = _lastPrices[2];
  _lastPrices[2] = _lastPrices[3];
  _lastPrices[3] = exchange;

  int increase = 3;

  for (size_t i = 0; i < 3; i++) {
    if (_lastPrices[i] < _lastPrices[i+1]) increase++;
    if (_lastPrices[i] > _lastPrices[i+1]) increase--;
  }

  if (increase == 0 && _numBitcoins > 0) {
    _numBitcoins--;
    _money += exchange;
  }
  if (increase == 6 && _money >= exchange) {
    _numBitcoins++;
    _money -= exchange;
  }
  if (_verbose && (increase == 0 || increase == 6)) {
    printf("Geld: %.2f, Bitcoins: %d, Wert eines Bitcoins: %.2f\n",
    _money, _numBitcoins, exchange);
  }
}

void Trader::printStatistics() const {
  printf("Startkapital:                       %.2f\n", _seedMoney);
  printf("Bitcoins zur Zeit:                  %d\n", _numBitcoins);
  printf("Geld zur Zeit:                      %.2f\n", _money);
  printf("Gewinn relativ zum Startkapital:    %.2f\n", _money-_seedMoney);
  printf("Geld insgesamt wenn Bitcoins\n");
  printf("zum aktuellen Kurs verkauft:        %.2f\n",
  _money+_numBitcoins*_lastPrices[3]);
  printf("Gewinn insgesamt wenn Bitcoins\n");
  printf("zum aktuellen Kurs verkauft:        %.2f\n",
  _money-_seedMoney+_numBitcoins*_lastPrices[3]);
}

#include "headers/Neuron.hpp"

double Neuron::error(double e){
    return (e-value)*(e-value);
}
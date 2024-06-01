#include <iostream>
#include <vector>
#include <cmath>

class Tensor {
private:
    std::vector<std::vector<double>> data;

public:
    Tensor(const std::vector<std::vector<double>>& input_data) : data(input_data) {}

    Tensor tensorProduct(const Tensor& second) const {
        std::vector<std::vector<double>> product_data;

        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < second.data.size(); ++j) {
                std::vector<double> product_row;
                for (size_t k = 0; k < data[i].size(); ++k) {
                    for (size_t l = 0; l < second.data[j].size(); ++l) {
                        product_row.push_back(data[i][k] * second.data[j][l]);
                    }
                }
                product_data.push_back(product_row);
            }
        }

        return Tensor(product_data);
    }

    Tensor normalize() const {
        double normalization_factor = calculateNormalizationFactor();
        std::vector<std::vector<double>> normalized_data;

        for (size_t i = 0; i < data.size(); ++i) {
            std::vector<double> normalized_row;
            for (size_t j = 0; j < data[i].size(); ++j) {
                normalized_row.push_back(data[i][j] / normalization_factor);
            }
            normalized_data.push_back(normalized_row);
        }

        return Tensor(normalized_data);
    }

    double calculateNormalizationFactor() const {
        double sum = 0.0;
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j) {
                sum += data[i][j] * data[i][j];
            }
        }
        return std::sqrt(sum);
    }

    size_t numRows() const {
        return data.size();
    }

    size_t numColumns() const {
        if (!data.empty()) {
            return data[0].size();
        }
        return 0;
    }

    void print() const {
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[i].size(); ++j) {
                std::cout << data[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
};

int main() {

    std::vector<std::vector<double>> data1 = {{1.0, 2.0},
                                              {3.0, 4.0}};
    std::vector<std::vector<double>> data2 = {{5.0, 6.0},
                                              {7.0, 8.0}};

    // std::vector<std::vector<double>> data1 = {{1.0, 2.0, 3.0},
    //                                           {4.0, 5.0, 6.0},
    //                                           {7.0, 8.0, 9.0}};
    
    // std::vector<std::vector<double>> data2 = {{10.0, 11.0, 12.0},
    //                                           {13.0, 14.0, 15.0},
    //                                           {16.0, 17.0, 18.0}};
                                                                               
    Tensor tensor1(data1);
    Tensor tensor2(data2);

    std::cout << "Tensor 1:" << std::endl;
    tensor1.print();
    std::cout << "Tensor 2:" << std::endl;
    tensor2.print();

    Tensor tensor_product = tensor1.tensorProduct(tensor2);
    std::cout << "Tensor Product:" << std::endl;
    tensor_product.print();

    double normalization_factor = tensor1.calculateNormalizationFactor();
    std::cout << "Normalization Factor: " << normalization_factor << std::endl;

    Tensor normalized_tensor = tensor_product.normalize();
    // std::cout << "Normalized Tensor Product:" << std::endl;
    // normalized_tensor.print();

    std::cout << "Number of Rows in the Tensor Product: " << normalized_tensor.numRows() << std::endl;
    std::cout << "Number of Columns in Tensor Product: " << normalized_tensor.numColumns() << std::endl;


    return 0;
}
#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
// IWYU pragma: no_include <__vector/vector.h>
#include <vector>  // IWYU pragma: keep

#include "backend/a_model.hpp"
#include "nodes/a_node.hpp"

/**
 * @class Model_mml
 * @brief A class representing a modular machine learning model.
 *
 * This class inherits from the Model class and represents a machine learning
 * model with a graph of nodes. It provides functionality to add nodes to the
 * graph and run inference on the graph.
 */
class Model_mml : public Model {
 public:
  /**
   * @brief Default constructor for Model_mml.
   *
   * Initializes an empty model.
   */
  Model_mml() = default;

  /**
   * @brief Constructor for Model_mml with initial nodes.
   *
   * @param initialNodes A std::vector of shared pointers to Node objects to
   * initialize the model with.
   */
  explicit Model_mml(std::vector<std::shared_ptr<Node>> initialNodes,
                     std::unordered_map<std::string, GeneralDataTypes> iomap,
                     std::vector<std::string> inputs,
                     std::vector<std::string> outputs)
      : nodes(std::move(initialNodes)),
        iomap(std::move(iomap)),
        inputs(std::move(inputs)),
        outputs(std::move(outputs)) {}

  /**
   * @brief Adds a node to the model graph.
   *
   * @param node A shared pointer to a Node object to be added to the graph.
   */
  void addNode(std::shared_ptr<Node> node) { nodes.push_back(std::move(node)); }

  /**
   * @brief Runs inference on the graph.
   *
   * @param tensor A reference to the input data for inference.
   * @return GeneralDataTypes The result of the inference.
   */
  std::unordered_map<std::string, GeneralDataTypes> infer(
      const std::unordered_map<std::string, GeneralDataTypes> &inputs) override;

 private:
  // Nodes in the graph
  std::vector<std::shared_ptr<Node>> nodes;

  // Map of inputs and outputs
  std::unordered_map<std::string, GeneralDataTypes> iomap;

  // Inputs and outputs
  std::vector<std::string> inputs;
  std::vector<std::string> outputs;

  // Helper std::function to do topological sort
  std::vector<std::vector<std::shared_ptr<Node>>> topologicalSort();
};
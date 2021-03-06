#include <fstream>
#include <iostream>

#include "boost/property_tree/json_parser.hpp"

#include "algorithms.h"
#include "moves_local_search.h"
#include "parse.h"

int main(int argc, const char *argv[]) {
  if (argc != 3 && argc != 4) {
    std::cout << "Usage: ./Main <input> <output> [<out_path>]" << std::endl;
    std::exit(-1);
  }
  std::ifstream in_file(argv[1]);
  if (!in_file) {
    std::cerr << "Error opening input file" << std::endl;
    std::exit(-1);
  }
  std::ofstream out_file(argv[2]);
  if (!out_file) {
    std::cerr << "Error opening output file" << std::endl;
    std::exit(-1);
  }
  PTree pt;
  boost::property_tree::json_parser::read_json(in_file, pt);
  Input input = parseInput(pt);
  std::cout << "Input file successfully parsed." << std::endl;
  State state(input);
  assignWithMinimumNumberPerGroup(state, MIN_GROUP_SIZE);
  assertMinNumCourse(state, CourseType::Mathe, 5);

  std::vector<int> num_ratings(NUM_RATINGS, 0);
  for (ParticipantID part = 0; part < state.numParticipants(); ++part) {
    Rating r = state.rating(part).at(state.assignment(part));
    int num = 1;
    if (state.isTeam(part)) {
      num = state.teamData(part).size();
    }
    num_ratings.at(r.index) += num;
  }
  for (uint32_t i = 0; i < NUM_RATINGS; ++i) {
    std::cout << "Number of " << Rating(i).getName() << ": "
              << num_ratings.at(i) << std::endl;
  }
  PTree result = writeOutputToTree(state);
  boost::property_tree::json_parser::write_json(out_file, result);
  if (argc == 4) {
    writeOutputToFiles(state, argv[3]);
  }
}

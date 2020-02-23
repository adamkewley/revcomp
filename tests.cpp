#include "gtest/gtest.h"

#include <fstream>

#define NO_MAIN
#include "revcomp.cpp"

using std::string;
using std::stringstream;
using std::ifstream;

TEST(revcomp, can_process_trivial_fasta_stream_without_throwing) {    
    stringstream input{};
    input << "> some seq name" << std::endl << "GATTACA" << std::endl;

    stringstream output{};    
    revcomp::reverse_complement_fasta_stream(input, output);
}

TEST(revcomp, returns_correct_data) {
    stringstream output{};
    {
        ifstream input_fixture{"revcomp-input.txt"};
        revcomp::reverse_complement_fasta_stream(input_fixture, output);
    }

    stringstream expected_output{};
    {
        ifstream output_fixture{"revcomp-output.txt"};
        expected_output << output_fixture.rdbuf();
    }

    ASSERT_EQ(output.str(), expected_output.str());    
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

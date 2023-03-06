#!/usr/bin/env bash

# Constants
input_dir="./tests/inputs/"
output_dir="./tests/outputs/"
ref_dir="./tests/refs/"

VALGRIND_ARGS="--tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=2 --track-origins=yes -q --log-file=rezultat_valgrind.txt"

# Create the output dir and build the executable
mkdir ${output_dir}
make clean
make build

valgrind_out="Erori valgrind:"
err_valgrind=0

# Points accumulator
result=0

# Iterate through tests
for in_file in ${input_dir}*; do
  # Get the name of the file
  base_name=${in_file##*/}
  prefix_name=${base_name%.*}

  # Declare point value for each test
  if [ ${prefix_name} == "g0e1" ]; then
    		declare -a p=(3)
  fi

  if [ ${prefix_name} == "g1e1" ]; then
        declare -a p=(5)
  fi

  if [ ${prefix_name} == "g1e2" ]; then
      		declare -a p=(6)
  fi

  if [ ${prefix_name} == "g1e3" ]; then
        declare -a p=(7)
  fi

  if [ ${prefix_name} == "g2e1" ]; then
        declare -a p=(6)
  fi

  if [ ${prefix_name} == "g2e2" ]; then
      		declare -a p=(8)
  fi

  if [ ${prefix_name} == "g2e3" ]; then
        declare -a p=(9)
  fi

  if [ ${prefix_name} == "g3e1" ]; then
        declare -a p=(4)
  fi

  if [ ${prefix_name} == "g3e2" ]; then
      		declare -a p=(7)
  fi

  if [ ${prefix_name} == "g3e3" ]; then
        declare -a p=(7)
  fi

  if [ ${prefix_name} == "g4e1" ]; then
        declare -a p=(7)
  fi

  if [ ${prefix_name} == "g4e2" ]; then
      		declare -a p=(9)
  fi

  if [ ${prefix_name} == "g4e3" ]; then
        declare -a p=(12)
  fi

  # Set output and refs files
  out_file=$(echo "${output_dir}${prefix_name}.out")
  ref_file=$(echo "${ref_dir}${prefix_name}.ref")

  # Run valgrind first
  valgrind $VALGRIND_ARGS ./tema3  < $in_file &> /dev/null
  EXIT_CODE=$?

  if [[ $EXIT_CODE -eq 2 ]]
  then
      echo "Memory leaks"
      echo "Test ${prefix_name} __________________ FAILED"
      valgrind_out="${valgrind_out}\n\n\n${prefix_name}\n$(cat rezultat_valgrind.txt)"
      err_valgrind=1
      continue
  else
      echo "No memory leaks"
  fi

  # Run the test
  ./tema3 < $in_file > $out_file
  toAdd=${p[i]}

  diff $out_file $ref_file > /dev/null

  EXIT_CODE=$?
  if [[ $EXIT_CODE -eq 0 ]]
    then
            echo "Test ${prefix_name} __________________ PASSED [$toAdd p]"
      result=$((result + toAdd))
    else
      echo "Test ${prefix_name} __________________ FAILED"
  fi
done

# Display results
echo "Result = $result/90"

echo -e "\n${valgrind_out}"

if [[ $err_valgrind -eq 0 ]]
  then
    echo -e "Nu exista erori\n"
fi

# Clean project
rm -r ${output_dir}
rm "rezultat_valgrind.txt"
make clean

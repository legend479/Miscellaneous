import argparse
import pytest
import json


def construct(file_str: str) -> dict[str, dict[str, float]]:
    """Takes in the string representing the file and returns pfsa
    The given example is for the statement "A cat"
    """

    PFSA = {"*":{}}
    
    file_str = file_str.lower().split()
    # print(file_str)

    for word in file_str:
        if word[0] not in PFSA["*"]:
            PFSA["*"][word[0]] = 0

        PFSA["*"][word[0]] += 1
        for i in range(len(word)-1):
            if word[:i+1] not in PFSA:
                PFSA[word[:i+1]] = {}
            
            if word[:i+2] not in PFSA[word[:i+1]]:
                PFSA[word[:i+1]][word[:i+2]] = 0
            
            PFSA[word[:i+1]][word[:i+2]] += 1
            # print(PFSA)
        if word not in PFSA:
            PFSA[word] = {}
        
        if word+"*" not in PFSA[word]:
            PFSA[word][word+"*"] = 0

        PFSA[word][word+"*"] += 1
        # print(PFSA)

    for key in PFSA:
        total = 0
        for key2 in PFSA[key]:
            total += PFSA[key][key2]
        for key2 in PFSA[key]:
            PFSA[key][key2] /= total

    return PFSA


def main():
    """
    The command for running is `python pfsa.py text.txt`. This will generate
    a file `text.json` which you will be using for generation.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("file", type=str, help="Name of the text file")
    args = parser.parse_args()

    with open(args.file, "r") as file:
        contents = file.read()
        output = construct(contents)

    name = args.file.split(".")[0]

    with open(f"{name}.json", "w") as file:
        json.dump(output, file)


if __name__ == "__main__":
    main()


STRINGS = ["A cat", "A CAT", "", "A", "A A A A"]
DICTIONARIES = [
    {
        "*": {"a": 0.5, "c": 0.5},
        "a": {"a*": 1.0},
        "c": {"ca": 1.0},
        "ca": {"cat": 1.0},
        "cat": {"cat*": 1.0},
    },
    {
        "*": {"a": 0.5, "c": 0.5},
        "a": {"a*": 1.0},
        "c": {"ca": 1.0},
        "ca": {"cat": 1.0},
        "cat": {"cat*": 1.0},
    },
    {
        "*": {},
    },
    {
        "*": {"a": 1.0},
        "a": {"a*": 1.0},
    },
    {
        "*": {"a": 1.0},
        "a": {"a*": 1.0},
    },
]


@pytest.mark.parametrize("string, pfsa", list(zip(STRINGS, DICTIONARIES)))
def test_output_match(string, pfsa):
    """
    To test, install `pytest` beforehand in your Python environment.
    Run `pytest pfsa.py` Your code must pass all tests. There are additional
    hidden tests that your code will be tested on during VIVA.
    """
    result = construct(string)
    assert result == pfsa
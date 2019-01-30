import re

if __name__ == "__main__":
    input_str = "  ( + 1 2 ) (print 1 2 )"
    
    regex_pattern = r'\(?.*?\)'
    matched_strs = re.findall(regex_pattern, input_str)
    print(matched_strs[0])
    print(matched_strs[1])

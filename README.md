# Advent of Code (2024)
I'm going back and solving some puzzles. The challenge is two-fold:
* Use C++ -- I've been using Python daily for the past two years, and could use some brushing up
* Solve without AI -- I sometimes worry I'll forget how to write code and solve problems with just my brain alone

### Usage
There's a `bash` script to create a new day directory:
```
$ ./new_day.sh
$ dayXX created from template
```

and a `python` script to scrape the problem descriptions
```
python get_prompt.py --year 2024 --day XX
```

### Dependencies
The solutions just use the `std` library.

The `python` scraper dependencies are contained in `requirements.txt`

```
pip install -r requirements.txt
```

The `python` scraper also requires that you store your `session` ID from your browser's cookies for [adventofcode.com](https://adventofcode.com) as an enviroment variable `SESSION_ID` or in a `.env` file. This is what enables it to retrieve the prompt for part 2 once you complete part 1... otherwise, it won't know who you are.
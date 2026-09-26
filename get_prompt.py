import dotenv
import argparse
import requests
import os
from bs4 import BeautifulSoup

dotenv.load_dotenv()


def parse(url):
    cookies = {"session": os.getenv("SESSION_ID")}
    response = requests.get(url, cookies=cookies)

    # 2. Parse the HTML using the built-in 'html.parser'
    soup = BeautifulSoup(response.text, "html.parser")

    descs = soup.find_all("article", class_="day-desc")

    print(descs[0])
    print(descs[1])


def main():
    parser = argparse.ArgumentParser(
        description=("A script to pull the prompt from Advent of Code website.")
    )

    parser.add_argument("-d", "--day", type=str, help="The day to retrieve")
    parser.add_argument(
        "-y",
        "--year",
        type=str,
        default="2024",
        help="The year to retrieve (default: 2024)",
    )

    # 3. Parse the arguments
    args = parser.parse_args()
    url = f"https://adventofcode.com/{args.year}/day/{args.day}"

    parse(url)


if __name__ == "__main__":
    main()

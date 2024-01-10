import requests
from typing import Dict

# connect to a "real" API

## Example: OpenWeatherMap
URL = "https://api.openweathermap.org/data/2.5/weather"
API_KEY = "d059471c13c01686c42ec541f9663b2b"

def get_weather(city) -> Dict:
    res = requests.get(URL, params={"q": city, "appid": API_KEY})
    return res.json()

#Additional API connection:
# URL = "https://apiv3.iucnredlist.org/api/v3/country/list"
# API_KEY = "r6g5dfs78g5g2r78gf876981dsb19d"

def main():
    temp = get_weather("London")
    print(temp)

if __name__ == "__main__":
    main()

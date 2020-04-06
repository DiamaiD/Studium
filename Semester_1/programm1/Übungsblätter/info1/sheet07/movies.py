#!/usr/bin/python3

class Movie:
    def __init__(self, title: str, year: int, rating: float):
        self.title = title
        self.year = year
        self.rating = rating

class Actor:
    def __init__(self, firstname: str, lastname: str, movies: list):
        self.firstname = firstname
        self.lastname = lastname
        self.movies = movies

def movie_str(movie: Movie) -> str:
    return "Movie('{0}', {1}, {2})".format(movie.title, movie.year, movie.rating)

def avg_score(movies: list) -> float:
    rating = 0.0
    for i in movies:
        rating += i.rating
    return rating/len(movies)

def worst_actor(actors: list) -> Actor:
    scores = []
    for actor in actors:
        scores.append(avg_score(actor.movies))
    index = scores.index(min(scores))
    return actors[index]
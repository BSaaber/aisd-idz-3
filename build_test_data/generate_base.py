import random
from pathlib import Path


def create_csv(filename: str, link_coef: float):
    Path(f'{filename}').mkdir(parents=True, exist_ok=True)
    for max_vertex in range(10, 1010 + 1, 50):
        # setup vars for this iteration
        vertexes = list(range(max_vertex))
        edges_set = set()

        # make graph linked
        vertexes_copy = vertexes.copy()
        random.shuffle(vertexes_copy)
        start = vertexes_copy[0]
        for i in range(1, len(vertexes_copy)):
            edges_set.add((start, i))
            start = i

        # create edges
        for k, i in enumerate(vertexes):
            v_copy = vertexes[:]
            random.shuffle(v_copy)
            j_vertexes = v_copy[:int(len(v_copy) * link_coef)]

            for j in j_vertexes:
                edges_set.add((j, i))

        # drop edges like (i, i)
        for i in range(max_vertex):
            edges_set.discard((i, i))

        # save data to file
        with open(f'{filename}/{max_vertex}.csv', 'w') as file:
            for i in edges_set:
                # vertex 1 of edge | vertex 2 of edge | weight of edge
                file.write(f'{i[0]},{i[1]},{random.randint(1, 10)}\n')



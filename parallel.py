import multiprocessing as mp

def process_wrapper(lineID):
    with open("texto.txt") as f:
        for i,line in enumerate(f):
            if i != lineID:
                continue
            else:
                process(line)
                break

#init objects
pool = mp.Pool(cores)
jobs = []

#create jobs
with open("texto.txt") as f:
    for ID,line in enumerate(f):
        jobs.append( pool.apply_async(process_wrapper,(ID)) )

#wait for all jobs to finish
for job in jobs:
    job.get()

#clean up
pool.close()
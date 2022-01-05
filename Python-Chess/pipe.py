class Pipe:
    def __init__(self, filename):
        self.p = open(filename, 'r+')

    def __del__(self):
        self.p.close()

    def read_from_pipe(self, length):
        self.p.seek(0)
        return self.p.read(length)

    def write_to_pipe(self, msg):
        self.p.write(msg)

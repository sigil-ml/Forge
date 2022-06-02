coverage run -m unittest discover -p '*test*.py' -s src/unittests/
coverage xml -o '/home/ubuntu/artifacts/coverage.xml'
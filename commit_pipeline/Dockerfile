FROM ubuntu:latest

LABEL image.author='SIGIL'

ENV PYTHON_VER=python3.9
ENV DEBIAN_FRONTEND noninteractive

# Install Neccessary Packages
RUN apt-get update && \
	apt-get install -y \
	${PYTHON_VER} \
	python3-sphinx \
	git \
	curl \
	wget \
	jq \
	python3-pip

RUN pip install --upgrade pip && \
	pip install \
	black \
	sphinx_rtd_theme 

# RUN wget https://github.com/snyk/cli/releases/download/v1.927.0/snyk-linux && \
# 	chmod +x ./snyk-linux && \
# 	./snyk-linux && \
# 	mv ./snyk-linux /bin/snyk && \
# 	snyk auth 173c26e0-9932-430c-9253-c4d37c8c8e8e

WORKDIR /home/AI-CI/


ENTRYPOINT sh commit_pipeline/commit.sh
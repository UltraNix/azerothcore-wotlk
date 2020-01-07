docker pull siof/sw-core-run-base:latest

copy dist/* /docker/core/dist

cd docker/core
docker build --tag sw-core-nb:local

pause

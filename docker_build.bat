docker pull siof/sw-build:latest

docker rm --force sunwell_wotlk
docker run --name sunwell_wotlk -it -v %~dp0:/build-src siof/sw-build:latest
pause

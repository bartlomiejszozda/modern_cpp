#docker build -t modern_cpp .
set -xeu
DOCKER_BUILDKIT=1 docker build --progress=plain -t modern_cpp .
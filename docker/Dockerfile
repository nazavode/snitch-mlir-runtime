FROM ghcr.io/pulp-platform/snitch@sha256:1a361160886ddee785ca809d0b9d30a283d0116b2761fd872ba9b69b82e2f2a6 as builder
RUN mkdir /src \
 && wget -q -O - https://github.com/nazavode/snitch/archive/a8f8d09b68e6bbf3923b53ab26cb105a11c9eee7.tar.gz | tar xzf - -C /src --strip-components 1 \
 && cd /src/hw/system/snitch_cluster \
 && make bin/snitch_cluster.vlt \
 && mkdir -p /opt/bin \
 && cp bin/snitch_cluster.vlt /opt/bin

FROM ghcr.io/pulp-platform/snitch@sha256:1a361160886ddee785ca809d0b9d30a283d0116b2761fd872ba9b69b82e2f2a6
COPY --from=builder /opt/bin/snitch_cluster.vlt /opt/bin/snitch_cluster.vlt

# Please remember to build with:
# --build-arg BUILD_DATE=$(date -u +'%Y-%m-%dT%H:%M:%SZ')
ARG BUILD_DATE

LABEL org.opencontainers.image.title="snitch-mlir-runtime-toolchain"
LABEL org.opencontainers.image.version="0.1"
LABEL org.opencontainers.image.description="Provides Snitch Verilator simulator and toolchains."
LABEL org.opencontainers.image.authors="glifi.05sneaker@icloud.com"
LABEL org.opencontainers.image.created=$BUILD_DATE

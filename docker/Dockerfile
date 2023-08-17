ARG SNITCH_MLIR_RUNTIME_COMMIT
ARG SNITCH_MLIR_RUNTIME_REPOSITORY=https://github.com/nazavode/snitch-mlir-runtime.git
ARG SNITCH_BASE_IMAGE=ghcr.io/pulp-platform/snitch@sha256:1a361160886ddee785ca809d0b9d30a283d0116b2761fd872ba9b69b82e2f2a6
ARG SNITCH_BASE_SOURCE=https://github.com/nazavode/snitch/archive/a8f8d09b68e6bbf3923b53ab26cb105a11c9eee7.tar.gz

FROM ${SNITCH_BASE_IMAGE} as builder

ARG SNITCH_BASE_IMAGE
ARG SNITCH_BASE_SOURCE

RUN mkdir /src \
 && wget -q -O - ${SNITCH_BASE_SOURCE} | tar xzf - -C /src --strip-components 1 \
 && cd /src/hw/system/snitch_cluster \
 && make bin/snitch_cluster.vlt \
 && mkdir -p /opt/bin \
 && cp bin/snitch_cluster.vlt /opt/bin

FROM ${SNITCH_BASE_IMAGE}

ARG SNITCH_MLIR_RUNTIME_REPOSITORY
ARG SNITCH_MLIR_RUNTIME_COMMIT

COPY --from=builder /opt/bin/snitch_cluster.vlt /opt/bin/snitch_cluster.vlt
RUN git clone ${SNITCH_MLIR_RUNTIME_REPOSITORY} /src \
 && cd /src \
 && git reset --hard ${SNITCH_MLIR_RUNTIME_COMMIT} \
 && cd /src/snitch-runtime \
 && make install PREFIX=/opt \
 && make clean \
 && cd /src/snitch-runtime \
 && make install PREFIX=/opt \
 && make clean

LABEL org.opencontainers.image.title="snitch-mlir-runtime"
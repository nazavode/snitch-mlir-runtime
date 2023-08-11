FROM ghcr.io/pulp-platform/snitch_cluster@sha256:aa1ccf9957514cc3b56621233b22bf75503bf06211e6ff7ee281d21c803ad2c9 as builder
RUN mkdir /src \
 && wget -q -O - https://github.com/pulp-platform/snitch_cluster/archive/1183399a1f2cdcad326f1f110146a008256c0c98.tar.gz | tar xzf - -C /src --strip-components 1 \
 && cd /src/target/snitch_cluster \
 && make bin/snitch_cluster.vlt \
 && mkdir -p /opt/bin \
 && cp /src/target/snitch_cluster/bin/snitch_cluster.vlt /opt/bin

FROM ghcr.io/pulp-platform/snitch_cluster@sha256:aa1ccf9957514cc3b56621233b22bf75503bf06211e6ff7ee281d21c803ad2c9
COPY --from=builder /opt/bin/snitch_cluster.vlt /opt/bin/snitch_cluster.vlt

# Please remember to build with:
# --build-arg BUILD_DATE=$(date -u +'%Y-%m-%dT%H:%M:%SZ')
ARG BUILD_DATE

LABEL version="0.1"
LABEL description="Provides Snitch Verilator simulator and toolchains."
LABEL maintainer="glifi.05sneaker@icloud.com"
LABEL org.label-schema.build-date=$BUILD_DATE
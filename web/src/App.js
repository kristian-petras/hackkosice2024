    import {Container, Box, Flex, Heading, Text, Card} from '@radix-ui/themes';
    import {
        BrowserRouter as Router,
        Routes,
        Route,
        Link
    } from "react-router-dom";


    export default function MyApp() {
      return (
          <Router>
              <Header />
              <Routes>
                  <Route path="/" element={<Composer/>} />
                  <Route path="/t2s" element={<T2S/>} />
              </Routes>
              <Footer />
          </Router>
      );
    }

    const Header = () => (
        <header className="header">
            <Container align="center" size="4" mb="8">
                <Card mt="4">
                    <Flex
                        direction="row"
                        justify="between"
                        p="2"
                        align="center"
                    >
                        <Box>
                            <Heading>B/S/H/</Heading>
                        </Box>
                        <Flex direction="row" gapX="3">
                            <Link to="/" weight="medium">Composer</Link>
                            <Link to="/t2s" weight="medium">Text to speech</Link>
                        </Flex>
                    </Flex>
                </Card>
            </Container>
        </header>
    );

    const Footer = () => (
        <footer className="footer">
            <Container align="center" size="4" mt="8">
                <Flex
                    direction="row"
                    justify="center"
                    align="center"
                    mb="4"
                >
                    <Text>Hack Košice &copy; {new Date().getFullYear()}</Text>
                </Flex>
            </Container>
        </footer>
    );

    const Composer = () => (
        <main>
            <Container size="4">
                <Heading as="h1" size="8">Composer</Heading>
            </Container>

            <Container>
                <Text>

                    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas interdum semper arcu, et dictum ipsum. Curabitur sagittis imperdiet ultricies. Duis facilisis turpis id nisi lobortis, quis gravida ipsum tempor. Duis condimentum eleifend ante. Praesent ac purus eros. Nunc dictum molestie est sed faucibus. Praesent ac enim eu leo volutpat ullamcorper vel eu mi. Vestibulum lacus massa, tincidunt id elementum non, rutrum sit amet metus. Mauris vel sem elit. In dolor est, tristique et venenatis non, auctor et mauris. Integer fermentum metus fringilla sem maximus blandit. Morbi congue justo ex, eu iaculis dui ullamcorper vitae. Proin eros tortor, molestie a arcu ac, convallis placerat massa.

                    Ut sollicitudin nibh eget augue suscipit, ut tincidunt augue scelerisque. Aliquam erat volutpat. Nam a quam vel nibh hendrerit tristique. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Cras iaculis dui leo, ac iaculis tortor efficitur vitae. Vivamus mollis, libero eu gravida pulvinar, diam libero congue mi, nec dapibus libero purus sed ligula. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed nibh diam, malesuada vel augue finibus, blandit eleifend nulla. Vestibulum vulputate auctor fermentum. Phasellus euismod felis non urna dignissim, quis finibus eros sollicitudin.

                    Suspendisse ultrices elit libero, a gravida massa euismod at. Aliquam eu magna a metus placerat vulputate. In venenatis diam et nibh hendrerit, in pulvinar erat iaculis. Donec pulvinar tortor eget nisl accumsan, a pulvinar diam bibendum. Donec quis luctus erat, vitae dapibus nisl. Curabitur arcu dolor, elementum facilisis massa quis, feugiat commodo nulla. Donec pulvinar leo diam, ut lobortis mauris maximus eget. Nam cursus sollicitudin velit, at tincidunt risus pretium non. Mauris sed augue lacinia, congue sapien ullamcorper, malesuada lorem. Nulla vitae tempus augue, eget egestas ipsum. Duis convallis diam sed orci bibendum interdum. Maecenas luctus at erat id aliquet. In venenatis tincidunt ante at consectetur.

                    Quisque feugiat porttitor quam, sit amet convallis magna sagittis non. Maecenas iaculis, dui sed pharetra eleifend, sem augue varius eros, id eleifend ligula velit vel libero. Pellentesque tellus purus, finibus in nisi nec, molestie semper eros. Suspendisse at viverra nisl, placerat blandit ex. Praesent congue et libero vitae facilisis. In eu egestas lectus. Aliquam nec mattis ante. Morbi accumsan quis turpis sit amet consectetur. Maecenas tincidunt vitae enim eu dictum. Fusce vitae euismod ante, quis aliquet ligula. Nullam semper ullamcorper ligula, eget vehicula dolor feugiat eget. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.

                    Aliquam hendrerit pellentesque elit, a pharetra lorem gravida eu. Fusce commodo nunc ut leo finibus, ac malesuada velit hendrerit. Nam tristique augue vitae arcu semper, non laoreet tellus tempor. Integer faucibus eros pretium placerat aliquam. Phasellus viverra, turpis elementum laoreet ullamcorper, risus arcu mattis nunc, nec tincidunt tellus turpis quis purus. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas ac finibus erat. Suspendisse varius dui quis gravida vulputate. Suspendisse non erat erat. Nunc ut tortor tortor. Pellentesque justo lorem, tempus at est nec, lobortis accumsan ligula.

                </Text>
            </Container>
        </main>
    )

    const T2S = () => (
        <main>
            <Container size="4">
                <Heading as="h1" size="8">Text to speech</Heading>
            </Container>

            <Container>
                <Text>

                    Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas interdum semper arcu, et dictum ipsum. Curabitur sagittis imperdiet ultricies. Duis facilisis turpis id nisi lobortis, quis gravida ipsum tempor. Duis condimentum eleifend ante. Praesent ac purus eros. Nunc dictum molestie est sed faucibus. Praesent ac enim eu leo volutpat ullamcorper vel eu mi. Vestibulum lacus massa, tincidunt id elementum non, rutrum sit amet metus. Mauris vel sem elit. In dolor est, tristique et venenatis non, auctor et mauris. Integer fermentum metus fringilla sem maximus blandit. Morbi congue justo ex, eu iaculis dui ullamcorper vitae. Proin eros tortor, molestie a arcu ac, convallis placerat massa.

                    Ut sollicitudin nibh eget augue suscipit, ut tincidunt augue scelerisque. Aliquam erat volutpat. Nam a quam vel nibh hendrerit tristique. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas. Cras iaculis dui leo, ac iaculis tortor efficitur vitae. Vivamus mollis, libero eu gravida pulvinar, diam libero congue mi, nec dapibus libero purus sed ligula. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed nibh diam, malesuada vel augue finibus, blandit eleifend nulla. Vestibulum vulputate auctor fermentum. Phasellus euismod felis non urna dignissim, quis finibus eros sollicitudin.

                    Suspendisse ultrices elit libero, a gravida massa euismod at. Aliquam eu magna a metus placerat vulputate. In venenatis diam et nibh hendrerit, in pulvinar erat iaculis. Donec pulvinar tortor eget nisl accumsan, a pulvinar diam bibendum. Donec quis luctus erat, vitae dapibus nisl. Curabitur arcu dolor, elementum facilisis massa quis, feugiat commodo nulla. Donec pulvinar leo diam, ut lobortis mauris maximus eget. Nam cursus sollicitudin velit, at tincidunt risus pretium non. Mauris sed augue lacinia, congue sapien ullamcorper, malesuada lorem. Nulla vitae tempus augue, eget egestas ipsum. Duis convallis diam sed orci bibendum interdum. Maecenas luctus at erat id aliquet. In venenatis tincidunt ante at consectetur.

                    Quisque feugiat porttitor quam, sit amet convallis magna sagittis non. Maecenas iaculis, dui sed pharetra eleifend, sem augue varius eros, id eleifend ligula velit vel libero. Pellentesque tellus purus, finibus in nisi nec, molestie semper eros. Suspendisse at viverra nisl, placerat blandit ex. Praesent congue et libero vitae facilisis. In eu egestas lectus. Aliquam nec mattis ante. Morbi accumsan quis turpis sit amet consectetur. Maecenas tincidunt vitae enim eu dictum. Fusce vitae euismod ante, quis aliquet ligula. Nullam semper ullamcorper ligula, eget vehicula dolor feugiat eget. Pellentesque habitant morbi tristique senectus et netus et malesuada fames ac turpis egestas.

                    Aliquam hendrerit pellentesque elit, a pharetra lorem gravida eu. Fusce commodo nunc ut leo finibus, ac malesuada velit hendrerit. Nam tristique augue vitae arcu semper, non laoreet tellus tempor. Integer faucibus eros pretium placerat aliquam. Phasellus viverra, turpis elementum laoreet ullamcorper, risus arcu mattis nunc, nec tincidunt tellus turpis quis purus. Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas ac finibus erat. Suspendisse varius dui quis gravida vulputate. Suspendisse non erat erat. Nunc ut tortor tortor. Pellentesque justo lorem, tempus at est nec, lobortis accumsan ligula.

                </Text>
            </Container>
        </main>
    )
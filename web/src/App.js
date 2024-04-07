    import {Button, Container, Box, Flex, Heading, Text, Card} from '@radix-ui/themes';
    import {
        BrowserRouter as Router,
        Routes,
        Route,
        Link
    } from "react-router-dom";
    import NoteGrid from "./NoteGrid";
    import T2VForm from "./T2VForm";

    export default function MyApp() {
      return (
          <Router>
              <Header />
              <Routes>
                  <Route path="/" element={<Composer/>} />
                  <Route path="/t2s" element={<T2S/>} />
                  <Route path="/playFromFile" element={<PlayFromFile/>} />
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
                            <Link to="/t2s" weight="medium">Text to Voice</Link>
                            <Link to="/playFromFile" weight="medium">Play from file</Link>
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
                <Heading as="h1" size="8" mb="3">Composer</Heading>
                <Text>
                    The composer allows users to create musical compositions by selecting notes, octaves, and specifying their duration. It presents a grid of buttons representing different notes and octaves. Users can click on these buttons to add musical elements to their composition. The composition can then be submitted for playback.
                </Text>
            </Container>

            <Container>
                <NoteGrid/>
            </Container>
        </main>
    )

    async function submitFile(filePicker) {
      console.log("banan");
      // Construct a FormData instance
      const formData = new FormData();

      // Add a file
      const selection = filePicker.files;
      if (selection.length > 0) {
        console.log("jahoda");
        const file = selection[0];
        formData.append("file", file);
      }

      try {
        const response = await fetch("http://127.0.0.1:8000/uploadfile/", {
          method: "POST",
          // Set the FormData instance as the request body
          body: formData,
        });
        console.log(await response.json());
      } catch (e) {
        console.error(e);
      }
    }

    const PlayFromFile = () => (
        <main>
            <Container size="4" mb="5">
                <Heading as="h1" size="8">Play from file</Heading>
                <input type="file" id="soundFileInput" onChange={ (event) => submitFile(event.target) }/>
            </Container>
        </main>
    )

    const T2S = () => (
        <main>
            <Container size="4">
                <Heading as="h1" size="8" mb="3">Text to Voice</Heading>
                <Text>
                    Lorem ipsum description...
                </Text>
            </Container>

            <Container>
                <T2VForm/>
            </Container>

        </main>
    )

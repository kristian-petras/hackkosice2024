    import {Button, Container, Box, Flex, Heading, Text, Card} from '@radix-ui/themes';
    import {
        BrowserRouter as Router,
        Routes,
        Route,
        Link
    } from "react-router-dom";
    import NoteGrid from "./NoteGrid";

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
                            <Link to="/t2s" weight="medium">Text to speech</Link>
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
            <Container size="4" mb="5">
                <Heading as="h1" size="8">Composer</Heading>
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

    async function submitTextToSpeech() {
        const ttsInput = document.getElementById("tts-input");
        console.log(ttsInput.value);
    }

    const T2S = () => (
        <main>
            <Container size="4" mb="5">
                <Heading as="h1" size="8">Text to speech</Heading>
            </Container>

            <input type="text" id="tts-input" />
            <Button onClick={ () => submitTextToSpeech() }>Say it</Button>
        </main>
    )

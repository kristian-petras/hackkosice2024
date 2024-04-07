    import {Button, Container, Box, Flex, Heading, Text, Card, Link} from '@radix-ui/themes';
    import {
        BrowserRouter as Router,
        Routes,
        Route,
        Link as RLink
    } from "react-router-dom";
    import NoteGrid from "./NoteGrid";
    import T2VForm from "./T2VForm";
    import PlayerInput from "./PlayerInput";

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
                        <Flex direction="row" gapX="5">
                            <Link asChild weight="medium">
                                <RLink to="/" weight="medium">Composer</RLink>
                            </Link>
                            <Link asChild weight="medium">
                                <RLink to="/t2s" weight="medium">Text to Voice</RLink>
                            </Link>
                            <Link asChild weight="medium">
                                <RLink to="/playFromFile" weight="medium">Play from file</RLink>
                            </Link>
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
                    direction="column"
                    justify="center"
                    align="center"
                    mb="4"
                >

                <Text>Hack Košice 2024 - bsh-challenge</Text>
                <Text>Peter Grocký - Edo Hopfer - Kristián Petráš - Simon Soroka</Text>

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

    const PlayFromFile = () => (
        <main>
            <Container size="3">
                <Heading as="h1" size="8" mb="3">Play from file</Heading>
                <Flex direction="column" gapY="3">
                    <Text>
                        This component provides an easy way for users to select an audio file from their device for further processing or playback. It presents a file selection input field where users can browse their local files to choose the audio file they wish to work with.
                    </Text>
                </Flex>
            </Container>
            <Container size="3">
                <PlayerInput/>
            </Container>
        </main>
    )

    const T2S = () => (
        <main>
            <Container size="4">
                <Heading as="h1" size="8" mb="3">Text to Voice</Heading>
                <Flex direction="column" gapY="3">
                <Text>
                    This tool is a web-based form designed to convert text input into spoken words, allowing users to generate audio from written content. The form consists of a text input area where users can type or paste the text they want to convert. Below the text input area, there is a button labeled "Speak🗣️". Clicking this button initiates the conversion process.
                </Text>

                <Text>
                    Once the user clicks the "Speak🗣️" button, the text entered in the input area is sent to a server for processing. The server then generates an audio representation of the text, which is returned to the user. This audio can be played back through the user's device speakers, allowing them to hear the spoken version of the text they provided.
                </Text>

                <Text>
                    The form provides a simple and intuitive interface for users to convert their text into speech. It can be useful for various purposes such as generating audio versions of documents, reading aloud text for accessibility purposes, or experimenting with text-to-speech technology.
                </Text>
                </Flex>
            </Container>

            <Container>
                <T2VForm/>
            </Container>
        </main>
    )

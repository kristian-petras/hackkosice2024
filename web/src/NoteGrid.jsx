import {Button, Card, Flex, Grid, Heading, Text, Box} from "@radix-ui/themes";
import { useState } from "react";
import { motion, AnimatePresence } from "framer-motion";

export default function NoteGrid() {
    const octaves = [0, 1, 2, 3, 4, 5, 6, 7, 8];
    const tones = [
        { note: 'C', color: 'gray' },
        { note: 'C#', color: 'gold' },
        { note: 'D', color: 'bronze' },
        { note: 'D#', color: 'brown' },
        { note: 'E', color: 'yellow' },
        { note: 'F', color: 'amber' },
        { note: 'F#', color: 'orange' },
        { note: 'G', color: 'tomato' },
        { note: 'G#', color: 'red' },
        { note: 'A', color: 'ruby' },
        { note: 'A#', color: 'crimson' },
        { note: 'B', color: 'pink' }
    ];

    const [selectedTones, setSelectedTones] = useState([]);

    const handleButtonClick = (className, id) => {
        setSelectedTones([...selectedTones, { className, id }]);
        console.log('Added tone:', className, 'with id:', id);
    };

    const emptyList = () => {
        setSelectedTones([]);
    }

    const removeFromList = (toneIndex) => {
        setSelectedTones(prevTones => {
            const updatedTones = [...prevTones];
            updatedTones.splice(toneIndex, 1);
            return updatedTones;
        });
    };

    const submitComposition = () => {
        const url = 'http://127.0.0.1:8000/playComposition';
        const origin = 'http://127.0.0.1:3000'; // Client origin


        const pointsJson = selectedTones.map((tone) => {
            const [note, octa, color] = tone.className.split("-");

            return { "note": note, "octave": parseInt(octa), "duration": 100 };
        });


        const data = {
            points: pointsJson
        };

        fetch(url, {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
                'Origin': origin
            },
            body: JSON.stringify(data)
        })
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok');
                }
                console.log(pointsJson);
                return response.json();
            })
            .then(data => {
                console.log('Response:', data);
            })
            .catch(error => {
                console.error('Error:', error);
            });
    };

    return (
        <>
            <Card mb="4">
                <Grid columns="9" gap="3" p="3" pb="5" pt="5">
                    {tones.map((tone, rowIndex) => (
                        octaves.map((item, colIndex) => {
                            const className = `${tone.note}-${item}-${tone.color}`;
                            const id = `${tone.note}-${item}`;
                            return (
                                <Button key={colIndex} variant="soft" color={tone.color}
                                        onClick={() => handleButtonClick(className, id)}>
                                    {tone.note + " - " + item}
                                </Button>
                            );
                        })
                    ))}
                </Grid>
            </Card>

            <Flex direction="row" gapX="3">
                <Box width="25%">
                    <Card >
                        <Flex direction="column" gapY="4">
                            <Heading as="h2" size="6" mb="2">Control Panel</Heading>
                            <Button>Pause</Button>
                            <Button onClick={() => emptyList()}>Remove All</Button>
                            <Button onClick={() => submitComposition()}>Submit ✅</Button>
                        </Flex>
                    </Card>
                </Box>

                <Box width="75%">
                    <Card>
                        <AnimatePresence>
                            {selectedTones.length > 0 && (
                                <>
                                    <Heading as="h2" size="6" mb="2">Timeline 🎵</Heading>
                                    <motion.div
                                        initial={{ opacity: 0, y: -20 }}
                                        animate={{ opacity: 1, y: 0 }}
                                        exit={{ opacity: 0, y: -20 }}
                                        transition={{ duration: 0.3 }}
                                    >
                                        <Flex direction="row" gap="3" wrap="wrap" pb="2" pt="3" >
                                            {selectedTones.map((tone, toneIndex) => {
                                                const [note, octa, color] = tone.className.split("-");
                                                return (
                                                    <Button key={toneIndex} variant="soft" color={color} onClick={() => removeFromList(toneIndex)} style={{ width: '80px' }}>
                                                        {note + " - " + octa}
                                                    </Button>
                                                );
                                            })}
                                        </Flex>
                                    </motion.div>
                                </>
                            )}
                            {selectedTones.length === 0 && (
                                <motion.div
                                    initial={{ opacity: 0, y: -20 }}
                                    animate={{ opacity: 1, y: 0 }}
                                    exit={{ opacity: 0, y: -20 }}
                                    transition={{ duration: 0.3 }}
                                >
                                    <Heading mb="2" mt="2">Timeline is empty 😔, please add some tunes🤩🎵!</Heading>
                                </motion.div>
                            )}
                        </AnimatePresence>
                    </Card>
                </Box>
            </Flex>
        </>
    );
}

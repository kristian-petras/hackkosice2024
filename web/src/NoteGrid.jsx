import { Button, Card, Flex, Grid, Heading, Text, Box, Slider } from "@radix-ui/themes";
import { useState } from "react";
import { motion, AnimatePresence } from "framer-motion";

const DurationSlider = ({ duration, onDurationChange }) => {
    const handleSliderChange = (value) => {
        onDurationChange(value);
    };

    return (
        <Flex direction="column" gap="2">
            <Text>Duration (s): {duration / 100}</Text>
            <Slider
                min={1}
                max={100}
                step={1}
                defaultValue={[25]}
                value={[duration]}
                onValueChange={handleSliderChange}
            />
        </Flex>
    );
};

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

    // Initialize duration with a default value
    const [duration, setDuration] = useState([25]);

    const handleDurationChange = (value) => {
        setDuration(value);
    };

    const [selectedTones, setSelectedTones] = useState([]);

    const handleButtonClick = (className, id, duration) => {
        if (duration === undefined) {
            duration = 25
        }
        setSelectedTones([...selectedTones, { className, id, duration }]);
        console.log('Added tone:', className, 'with id:', id, 'Duration:', duration[0] * 10);
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
            const [note, octa, color, _duration] = tone.className.split("-");

            return { "note": note, "octave": parseInt(octa), "duration": parseInt(_duration)};
        });

        const data = {
            points: pointsJson
        };

        console.log(data);
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
            <Card mb="4" mt="3">
                <Grid columns="9" gap="3" p="3" pb="5" pt="5">
                    {tones.map((tone, rowIndex) => (
                        octaves.map((item, colIndex) => {
                            const className = `${tone.note}-${item}-${tone.color}-${duration*10}`;
                            const id = `${tone.note}-${item}`;
                            return (
                                <Button key={colIndex} variant="soft" color={tone.color}
                                        onClick={() => handleButtonClick(className, id, duration)}>
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
                            <DurationSlider duration={duration} onDurationChange={handleDurationChange}/>
                            <Button>Pause</Button>
                            <Button onClick={() => emptyList()} disabled={selectedTones.length === 0}>Remove All</Button>
                            <Button onClick={() => submitComposition()} disabled={selectedTones.length === 0}>Submit ✅</Button>
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
                                                const [note, octa, color, _duration] = tone.className.split("-");
                                                const _width = 74 + parseInt(_duration ) / 10;
                                                return (
                                                    <Button key={toneIndex} variant="soft" color={color} onClick={() => removeFromList(toneIndex)} style={{ width: `${_width}px` }}>
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
    )
}

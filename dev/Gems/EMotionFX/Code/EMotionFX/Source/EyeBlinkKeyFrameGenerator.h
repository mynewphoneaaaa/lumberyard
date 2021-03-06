/*
* All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
* its licensors.
*
* For complete copyright and license terms please see the LICENSE at the root of this
* distribution (the "License"). All use of this software is governed by the License,
* or, if provided, by the license below or the license accompanying this file. Do not
* remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*
*/

#pragma once

// include the required headers
#include "EMotionFXConfig.h"
#include "KeyFrameGenerator.h"


namespace EMotionFX
{
    /**
     * The eye blink generator.
     * This class can automatically generate keyframes in a keytrack of floats (KeyTrackLinear<float>), which will simulate
     * the blinking of the eyes. This class is used inside LM Studio to automate the keyframing of the eyes.
     * It can theoretically also be used for other things, which have similar behaviour.
     */
    class EMFX_API EyeBlinkKeyFrameGenerator
        : public KeyFrameGenerator<float, MCore::Compressed16BitFloat>
    {
    public:
        /**
         * The unique ID of this generator.
         */
        enum
        {
            TYPE_ID = 0x00000001
        };

        /**
         * The creation method.
         */
        static EyeBlinkKeyFrameGenerator* Create();

        /**
         * Setup the properties of the generator.
         * @param startTime The time (in seconds) where we can generate the first key.
         * @param endTime The end time (in seconds) where we can generate the last key.
         * @param interval The average time (in seconds) between the eye blinks.
         * @param randomness The randomness (in seconds) of the interval, this must be smaller than (interval - blinkSpeed).
         * @param blinkSpeed The time (in seconds) which it takes to make an eye blink, so how fast we open and close the eyes.
         */
        void SetProperties(float startTime, float endTime, float interval, float randomness, float blinkSpeed);

        /**
         * The main method, which applies the generator on a given keytrack.
         * Before you call the generate method you might want to set the properties of the generator, if it has any.
         * Please note that existing keys in the keytrack will not be removed before we add keys generated by this generator.
         * @param outTrack A pointer to the keytrack to write the keyframes in.
         */
        void Generate(KeyTrackLinear<float, MCore::Compressed16BitFloat>* outTrack) override;

        /**
         * Get the description of the generator.
         * This should be the class name as a string.
         * @result The string containing the description of the generator.
         */
        const char* GetDescription() const override;

        /**
         * Get the unique type identification number of this class.
         * It can be used to detect the keyframe generator types.
         * @result The unique ID of this class.
         */
        uint32 GetType() const override;

        /**
         * Get the start time of the generator.
         * @result The start time (in seconds) on which the first key will be generated.
         */
        float GetStartTime() const;

        /**
         * Get the end time of the generator.
         * @result The end time (in seconds) on which the last key will be generated.
         */
        float GetEndTime() const;

        /**
         * Get the randomness value.
         * This is the displacement being applied on the interval, to prevent blinks at evenly spaced intervals.
         * @result The randomness value (in seconds).
         */
        float GetRandomness() const;

        /**
         * Get the interval, which is the time between the eye blinks (when randomness is set to zero).
         * @result The interval (in seconds) between the eye blinks.
         */
        float GetInterval() const;

        /**
         * Get the blink speed.
         * This returns the time in seconds, which it takes to go from open eyes to closed eyes and to open eyes again.
         * @result The blink speed, in seconds.
         */
        float GetBlinkSpeed() const;


    private:
        float   mStartTime;     /**< The start time. */
        float   mEndTime;       /**< The end time. */
        float   mInterval;      /**< The interval (in seconds), which is after how many seconds a blink should happen. */
        float   mRandomness;    /**< The randomness (in seconds) which should be applied to the interval. */
        float   mBlinkSpeed;    /**< The eye blink speed (in seconds). */

        /**
         * Align a given input time value to a certain FPS.
         * @param timeValue The input time value, in seconds.
         * @param framesPerSecond The frames per second to align to.
         * @result The aligned time value in seconds.
         */
        float AlignToFPS(float timeValue, uint32 framesPerSecond);

        /**
         * The constructor.
         */
        EyeBlinkKeyFrameGenerator();

        /**
         * The destructor.
         */
        ~EyeBlinkKeyFrameGenerator();
    };
} // namespace EMotionFX


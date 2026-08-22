# Stage 1 — Fire Castle
## Vertical Slice Execution Plan

**Document type:** Production planning document; not a full level build  
**Stage:** 1 — Fire Castle  
**Prepared by:** Manus AI  
**Status:** Ready for team planning, review, and task breakdown

> **Scope note.** The Game Design Bible was not present in the accessible workspace or available GitHub repositories at the time of preparation. This plan therefore treats **Fire Castle** as the authoritative stage theme and defines a production-ready vertical-slice baseline around that premise. Any Bible-specific names, narrative beats, enemy rosters, metrics, or platform constraints should replace the marked assumptions during the first design review; the execution structure should remain intact.

## 1. Vertical Slice Objective

The Fire Castle slice must prove that the stage can deliver a complete, representative player experience from entry to a clear end-state. It should demonstrate the intended **combat rhythm, traversal language, environmental hazard logic, visual identity, encounter escalation, and reward cadence** without requiring the entire production level.

The slice is successful when a new player can enter the castle, understand the primary fire-based threat, use the stage’s signature interaction to advance, survive a compact escalation of encounters, and reach a readable culmination encounter or exit. The build should be short enough to iterate rapidly, but complete enough that design, art, engineering, audio, and QA can evaluate the stage as a coherent experience rather than as disconnected mechanics.

### Target slice shape

| Dimension | Working target | Purpose |
|---|---:|---|
| Playable route | One authored critical path with one optional reward branch | Tests pacing and meaningful exploration without multiplying scope |
| Runtime | Approximately 8–12 minutes for a first-time player | Long enough to establish a loop; short enough for repeated review |
| Major spaces | 5 gameplay beats plus entry and exit | Provides a beginning, escalation, climax, and resolution |
| New-player learning | Teach → apply → combine → test under pressure | Makes the signature mechanics legible |
| Combat encounters | 3 authored encounters plus a final pressure encounter | Demonstrates escalation without requiring the full enemy catalog |
| Save/restart | One restartable slice checkpoint | Supports repeated playtest and regression testing |
| Art target | Cohesive representative environment, not final production coverage | Validates mood, readability, and visual hierarchy |

## 2. Assumptions and Non-Goals

The plan assumes a third-person or first-person action-adventure structure in which the player can move through a castle interior and interact with a fire-themed environment. If the Game Design Bible specifies a different camera, genre, or player ability set, the required substitutions should be made at the mechanic mapping review rather than by expanding the slice.

The slice does **not** attempt to build the full Fire Castle, finalize every asset, implement the complete enemy roster, author all narrative content, or solve every performance target for the complete game. It also does not include systemic procedural generation, a complete progression tree, multiplayer support, or polish work that cannot be evaluated within the slice’s critical path.

| Included in the slice | Explicitly deferred |
|---|---|
| One polished critical path | Full castle layout and all side rooms |
| Three must-have mechanics | Full ability/progression system |
| Representative enemies and hazards | Complete enemy taxonomy |
| Signature set-piece or climax | Full boss production, unless required by the Bible |
| Functional checkpoint and restart | Global save architecture |
| Representative lighting, VFX, audio, and UI | Final asset replacement across the game |
| Instrumented playtest build | Full release certification |

## 3. Three Must-Have Mechanics

### Mechanic 1 — Heat, Fire, and Safe-Zone Management

The level must communicate that **fire is both a threat and a navigational state**. The player enters hazardous heat volumes, reads their warning language, moves through or around them, and uses clearly identifiable safe zones to recover or re-plan. Fire hazards should have a predictable telegraph, a fair active window, and a readable consequence.

**Minimum implementation:** one persistent hazard type, one timed or pulsing hazard variant, a visible warning state, a damage or status consequence, and at least one route where choosing the correct safe zone is more efficient than simply waiting.

**Proof moment:** the player crosses a short hazard corridor after observing the warning pattern, then later performs the same read while also managing an enemy encounter.

### Mechanic 2 — Fire-Driven Environmental Interaction

The player must use a stage-specific interaction to change the environment. The interaction may be ignition, extinguishing, redirecting heat, activating a furnace, breaking a fire seal, or another Bible-defined action. It must create a visible before/after state and open or alter the route rather than functioning as a purely cosmetic switch.

**Minimum implementation:** one tutorial interaction, one gated progression interaction, and one optional interaction that reveals a reward or shortcut. Each interaction needs a clear affordance, activation feedback, state persistence for the current run, and failure-safe behavior.

**Proof moment:** the player first performs the interaction in a safe context, then applies it while a hazard or enemy creates pressure.

### Mechanic 3 — Layered Encounter Pressure

The slice must combine traversal hazards and combat so that the player cannot treat the stage as only a corridor or only an arena. The encounter grammar should escalate from a clean introduction to a mixed-space challenge in which positioning, timing, and use of the environmental interaction matter together.

**Minimum implementation:** one introductory combat encounter, one mixed hazard-and-combat encounter, and one final pressure encounter or mini-climax. At least one encounter must allow more than one viable position or approach, while still preserving a readable intended solution.

**Proof moment:** the player uses the environmental interaction to create an advantage, safe route, or temporary opening during an encounter rather than waiting for the room to become passive.

## 4. Level Blockout Milestones

The milestones below are ordered to prevent art production from hiding unresolved gameplay problems. Each milestone has a concrete exit condition and should end with a playable build or reviewable artifact.

| Milestone | Blockout scope | Key questions | Exit condition |
|---|---|---|---|
| M0 — Slice contract | Define the critical path, intended player verbs, stage start/end, and excluded scope | What must be proven, and what can be cut without invalidating the slice? | Signed one-page scope map and mechanic-to-space matrix |
| M1 — Greybox route | Entry, tutorial chamber, hazard corridor, first combat room, transition, climax room, exit | Can the player understand where to go and move without art or VFX? | Complete route is traversable from start to end with placeholder geometry |
| M2 — Traversal and hazard pass | Add collision, ledges, gaps, safe zones, hazard volumes, reset points, and basic timing | Is the fire threat fair, legible, and paced? | First-time tester reaches the exit without designer intervention; no progression blocker remains |
| M3 — Encounter pass | Place representative enemies, spawn logic, arena boundaries, cover/height options, and encounter gates | Does combat pressure support rather than obscure the stage’s signature mechanic? | Three encounters are repeatable, resettable, and beatable with stable spawn behavior |
| M4 — Mechanic integration pass | Implement fire interaction states, progression gate, optional branch, and combined encounter | Does the stage teach and then recombine the mechanics? | All three must-have mechanics appear in at least two distinct contexts |
| M5 — Pacing and readability pass | Tune distances, sightlines, telegraphs, room transitions, checkpoints, and recovery windows | Does the slice have a beginning, escalation, climax, and release? | Internal playtest shows no unexplained dead time or abrupt difficulty spike |
| M6 — Representative art pass | Replace primary silhouettes, establish material language, lighting zones, VFX placeholders, and landmark dressing | Can players read hazards, interactables, enemies, and objectives at a glance? | Art-complete critical path supports gameplay readability at target camera distance |
| M7 — Audio, UI, and feedback pass | Add hazard cues, interaction confirmation, damage feedback, objective messaging, and checkpoint feedback | Does the player receive confirmation without relying on a designer’s explanation? | A silent observer can identify major state changes from play and feedback |
| M8 — Stabilization and review candidate | Fix blocking defects, capture metrics, verify restart, and prepare a review build | Is the slice stable enough for cross-discipline acceptance? | No open Blocker or Critical defects; acceptance checklist is reviewable in one sitting |

## 5. Recommended Space Sequence

The route should be built as a compact sequence of spaces, each with one dominant job. The names are functional placeholders and should be renamed to match the Game Design Bible once available.

| Beat | Space | Player experience | Required content |
|---|---|---|---|
| 0 | Ashen Approach | Establish silhouette, heat threat, and destination | Castle exterior threshold, landmark view, low-risk movement |
| 1 | Ember Gate | Teach the environmental interaction | Safe interaction, clear state change, first route unlock |
| 2 | Furnace Gallery | Teach heat timing and recovery | Pulsing fire hazard, safe zones, readable telegraph |
| 3 | Guard Barracks | Establish combat baseline | Introductory enemy group, simple geometry, checkpoint afterward |
| 4 | Cinderworks | Combine mechanics under pressure | Mixed hazard/combat encounter, optional reward branch |
| 5 | Crown Chamber | Deliver culmination and test mastery | Final pressure encounter or compact mini-climax, strong landmark |
| 6 | Cooling Hall / Exit | Confirm success and provide release | Exit gate, reward/state confirmation, restart-safe endpoint |

## 6. Asset List

The asset list is deliberately sized for a vertical slice. Assets should be authored first for **readability, reuse, and state variation**, then expanded only after the slice proves its gameplay value.

### Environment and modular kit

| Asset group | Required slice assets | Notes |
|---|---|---|
| Structural kit | Floor, wall, ceiling, arch, doorway, stair, platform, bridge, pillar, battlement, trim pieces | Prioritize modular dimensions and clean collision |
| Fire Castle identity | Obsidian or scorched masonry material, ember-veined stone, ironwork, furnace brick, banners, crest or landmark motif | One coherent material language is more important than asset count |
| Interactive architecture | Fire seal, brazier/furnace, valve or lever, gate, pressure plate or trigger proxy | Each interactive asset needs clear inactive, active, and locked states |
| Hazard kit | Flame jet, lava/fire fissure, burning grate, heat-volume proxy, ash vent, extinguished variant | Hazard shapes must remain readable under gameplay lighting |
| Traversal support | Ladders, climbable markers, railings, cover blocks, drop/reset volumes, collision blockers | Keep collision simpler than render geometry |
| Set dressing | Chains, rubble, broken weapons, crates, ash piles, embers, hanging iron, cracked masonry | Use dressing to guide the critical path, not to add visual noise |
| Landmark | Castle crown, furnace core, fire throne, tower silhouette, or Bible-defined focal object | Must be visible from at least two beats to support orientation |

### Characters, enemies, and gameplay objects

| Asset group | Required slice assets | Acceptance intent |
|---|---|---|
| Player | Existing player model, locomotion, damage/death states, interaction animation or proxy | Must support all three mechanics without animation blocking |
| Enemy set | One baseline melee enemy, one ranged or area-denial enemy, one elite/pressure variant | Use the smallest roster that demonstrates encounter escalation |
| Encounter objects | Spawn markers, encounter gate, arena boundary, reward container, checkpoint object | States must be visible and resettable |
| Collectible/reward | One optional reward type and one completion reward | Reward must communicate why the optional route exists |
| UI elements | Objective prompt, interaction prompt, health/heat feedback, checkpoint notification, completion message | Use temporary UI if final UI is not yet available, but keep hierarchy stable |

### VFX, lighting, audio, and technical assets

| Asset group | Required slice assets | Notes |
|---|---|---|
| VFX | Ambient embers, flame burst, heat distortion, ignition/extinguish response, hit feedback, hazard warning, enemy death feedback | Every gameplay state change needs at least one nonverbal cue |
| Lighting | Warm fire key, cool safe-zone contrast, hazard readability pass, climax lighting state, baked/probe or equivalent setup | Avoid lighting that makes hazard boundaries ambiguous |
| Audio | Fire loop, hazard warning, interaction activation, gate transition, enemy cues, player damage, checkpoint, completion sting | Cues should remain distinguishable during combat |
| Technical | Collision volumes, navigation data, spawn configuration, checkpoint data, reset script, debug toggles, performance markers | Debug toggles should be available in the review build |

## 7. Execution Workstreams and Dependencies

The work should proceed in vertical slices rather than by completing entire disciplines independently. Greybox and mechanic validation come first; representative art should begin only after the route and interaction states are stable enough to avoid re-authoring every asset.

| Workstream | Starts after | Deliverable | Main dependency |
|---|---|---|---|
| Design | M0 | Beat sheet, route map, encounter intent, tuning sheet | Scope contract |
| Level design | M0 | Greybox route and pacing revisions | Player movement and collision |
| Engineering | M0 | Hazard, interaction, checkpoint, reset, and encounter systems | Design state definitions |
| Environment art | M2 | Modular kit, landmark, primary materials, readable set dressing | Stable blockout dimensions |
| Character/enemy | M2 | Representative enemy set and required states | Existing combat framework |
| VFX/lighting | M3 | Hazard and interaction feedback, stage lighting pass | Stable gameplay states |
| Audio/UI | M4 | Feedback cues and objective/readability support | Finalized interaction and encounter events |
| QA | M1 | Test cases, defect triage, regression runs | Playable build and debug access |

## 8. Test Checklist

Testing should be performed in the order below, because a failure in route completion or state reset invalidates most downstream polish observations. Each test should record build number, platform, tester, result, and defect ID where applicable.

### Functional and progression tests

- [ ] A new game starts at the intended Fire Castle entry point with the correct player state.
- [ ] The player can traverse the entire critical path without developer-only movement or collision bypasses.
- [ ] The tutorial interaction is discoverable, activatable, and produces the intended environmental state change.
- [ ] The progression gate remains closed before the required state is achieved and opens afterward.
- [ ] The optional branch can be entered, completed, and exited without blocking the critical path.
- [ ] The endpoint displays a clear completion or transition state.
- [ ] The checkpoint can be activated, used, and restarted repeatedly.
- [ ] Death, reset, reload, and checkpoint restart return hazards, enemies, gates, and interactables to valid states.

### Mechanic tests

- [ ] Heat/fire hazards have a readable warning, active, and recovery or inactive state.
- [ ] Hazard damage or status application is consistent across repeated trials.
- [ ] Safe zones are visually and mechanically safe; their boundaries do not contradict their appearance.
- [ ] Environmental interactions provide immediate visual, audio, and state feedback.
- [ ] Locked, available, active, and completed interaction states are distinguishable.
- [ ] At least one encounter requires or strongly rewards use of the environmental interaction.
- [ ] The combined mechanic sequence remains beatable after a restart and does not depend on stale state.

### Combat and pacing tests

- [ ] Enemy spawns occur once per intended trigger and do not duplicate after re-entry or reset.
- [ ] Enemies do not spawn inside geometry, outside the playable area, or behind an unintended one-way blocker.
- [ ] Encounter gates open only after the correct completion condition.
- [ ] The player has a readable recovery opportunity between major beats.
- [ ] No single hazard or enemy hit creates an unavoidable death loop.
- [ ] The climax is materially more demanding than the introduction but does not introduce an unexplained rule.
- [ ] The optional reward branch has a meaningful but non-blocking risk/reward relationship.

### Readability, audio, and accessibility tests

- [ ] The critical path is identifiable without waypoint assistance after the first pass.
- [ ] Fire hazards, interactables, enemies, and safe zones remain distinguishable in motion.
- [ ] Visual effects do not obscure enemy attacks, player damage, or traversal edges.
- [ ] Audio cues remain distinguishable when multiple fire and combat sounds overlap.
- [ ] Subtitle, prompt, color, and contrast settings follow the project’s accessibility baseline.
- [ ] The experience remains understandable with audio muted, using visual feedback alone.
- [ ] The experience remains playable with reduced visual effects, if that option exists.

### Technical and regression tests

- [ ] The slice loads from a clean boot and from the checkpoint without errors.
- [ ] No blocker-level crashes, soft locks, missing collision, or progression dead ends remain.
- [ ] Frame-time and memory behavior are within the project’s agreed review-build budget on the target platform.
- [ ] Streaming, lighting, VFX, and audio transitions do not produce visible or audible stalls.
- [ ] Debug overlays can be enabled to inspect hazard volumes, spawn points, interaction states, and checkpoint state.
- [ ] A second complete playthrough produces the same progression result unless variation is intentional.

## 9. Acceptance Criteria

The Fire Castle Vertical Slice is accepted only when the following criteria are met. “Mostly working” is not sufficient for the must-have mechanics: every mechanic must be observable, repeatable, and connected to progression or encounter decision-making.

| Area | Acceptance criterion | Evidence |
|---|---|---|
| Route completion | A first-time player can reach the end of the slice without designer instructions after the initial build briefing | Recorded playtest and route-completion log |
| Critical path | Entry, teaching beat, application beat, combined challenge, climax, and exit are all present and connected | Current build plus annotated route map |
| Mechanic 1 | Heat/fire hazards are legible, fair, repeatable, and consequential | Hazard test results and gameplay capture |
| Mechanic 2 | The fire-driven interaction changes the environment and is used in both progression and optional or encounter context | State diagram, test cases, capture |
| Mechanic 3 | At least three encounters demonstrate increasing pressure, including one mixed hazard/combat encounter | Encounter sheet and playtest results |
| Feedback | Major state changes have readable visual, audio, or UI confirmation; no critical state depends on hidden information | Readability review notes |
| Pacing | The slice has a discernible beginning, escalation, climax, and release, with no unintentional dead-end or extended idle segment | Timing sheet from at least three playthroughs |
| Restartability | Death and checkpoint restart restore a valid, playable state in every authored beat | Repeated reset test results |
| Presentation | The critical path communicates Fire Castle’s visual and tonal identity using representative materials, lighting, VFX, audio, and landmark dressing | Cross-discipline review build |
| Stability | No open Blocker/Critical defects; all known High defects have an owner and documented disposition | QA report and issue tracker |
| Scope control | The build remains within the approved slice boundaries; deferred content has not become a hidden dependency | Scope checklist and review sign-off |

### Definition of done

The slice is **Done for vertical-slice review** when the acceptance table is satisfied, the build can be restarted from a clean state, the three must-have mechanics have been observed by an external reviewer, and the team can explain which elements are representative prototypes versus production-final content. Any remaining limitations must be documented as explicit follow-up work rather than left ambiguous.

## 10. Playtest Metrics and Review Questions

The team should capture lightweight measures rather than optimize prematurely. The goal is to discover whether the stage communicates its rules and whether the intended route produces the desired experience.

| Metric | How to collect | Review signal |
|---|---|---|
| Time to first interaction | Timestamp entry to first successful use | If high, the interaction is not discoverable enough |
| Time to first hazard failure | First exposure to first damage/death | If immediate and repeated, telegraphing or recovery is insufficient |
| Critical-path completion rate | Percentage reaching the exit | Low rate indicates route, difficulty, or state issues |
| Optional-branch engagement | Percentage entering and completing branch | Very low may indicate weak signposting or reward value |
| Checkpoint recovery success | Successful restarts without soft lock | Any failure is a release-blocking defect for the slice |
| Encounter retry count | Attempts per encounter | Helps distinguish intended challenge from unreadable failure |
| Unprompted rule explanation | Ask testers to explain fire hazard and interaction | If they cannot, feedback or teaching needs revision |

The review should answer five questions in sequence: Can the player tell where the castle wants them to go? Can the player predict what fire will do? Can the player understand how the stage-specific interaction changes the space? Does combining hazards and enemies create deliberate pressure rather than confusion? Does the final beat feel like a meaningful test of what was taught?

## 11. Risks, Cuts, and Contingencies

The primary production risk is building a visually impressive castle before the signature interaction and hazard language are validated. The team should protect the mechanic proof above decorative coverage. If schedule pressure occurs, reduce room count and asset variety before removing mechanic contexts or the climax beat.

| Risk | Early warning | Mitigation | Safe cut |
|---|---|---|---|
| Fire hazards are unreadable in combat | Testers take damage without identifying the source | Increase telegraph duration, contrast, and audio separation | Remove secondary hazard variant |
| Interaction feels like a generic switch | Players activate it without understanding the consequence | Add visible before/after state and route payoff | Remove optional interaction, retain progression interaction |
| Combat overwhelms traversal | Players ignore safe zones and route cues | Reduce enemy count, widen combat space, stagger spawns | Remove elite variant |
| Scope expands through dressing | Art requests exceed route needs | Enforce landmark, primary silhouette, and reuse priorities | Reduce secondary set dressing |
| Reset state is unreliable | Re-entry changes gate or spawn state | Centralize state reset and add debug reset command | Remove nonessential persistence |
| Climax lacks payoff | Final room feels like another encounter | Strengthen landmark, reward, and transition feedback | Shorten preceding room, do not remove climax |

## 12. Sign-Off Sequence

The design owner signs off the route and mechanic proof after M4. The engineering and QA owners sign off reset, progression, and stability after M5. Art, VFX, audio, and UI owners sign off representative readability after M7. The final vertical-slice review occurs at M8 with the acceptance criteria, test report, open-defect list, and known-limitations note presented together.

The final review package should contain the playable build, annotated route map, mechanic state diagrams, asset inventory, test report, short playthrough capture, and a one-page list of deferred work. This package makes the slice useful as both a production gate and a reference target for the remaining Fire Castle content.

## References

[1]: #stage-1--fire-castle "This plan's Fire Castle vertical-slice scope and execution sections"
[2]: #three-must-have-mechanics "This plan's must-have mechanic definitions"
[3]: #acceptance-criteria "This plan's acceptance criteria and definition of done"

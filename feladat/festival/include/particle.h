// particle.h

#ifndef PARTICLE_H
#define PARTICLE_H

#define MAX_PARTICLES 1000  // Maximum number of particles in a system.

typedef struct {
    float x, y, z;  // Particle position.
    float vx, vy, vz;  // Particle velocity.
    float life;  // Particle life remaining, in seconds.
} Particle;

typedef struct {
    Particle particles[MAX_PARTICLES];
    int num_particles;  // The actual number of particles in use.
} ParticleSystem;

// Initialize a Particle.
void particle_init(Particle* p, float x, float y, float z, float vx, float vy, float vz, float life);

// Initialize a ParticleSystem.
void particle_system_init(ParticleSystem* ps, float x, float y, float z, int num_particles);

// Update a Particle's position based on its velocity.
void particle_update(Particle* p, float dt);

// Update all particles in a ParticleSystem.
void particle_system_update(ParticleSystem* ps, float dt);

// Render a Particle.
// Note: this function assumes a rendering context is already set up.
void particle_render(const Particle* p);

// Render all particles in a ParticleSystem.
void particle_system_render(const ParticleSystem* ps);

#endif // PARTICLE_H
